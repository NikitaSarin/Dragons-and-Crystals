//
// Created by nikita on 10/28/17.
//

#include <sstream>
#include "Controller.h"

Model* Controller::model = nullptr;
bool Controller::exitCode = false;

Controller::Controller(Model *m) {
    model = m;
    commands["N"] = unique_ptr<Commands>(new N());
    commands["S"] = unique_ptr<Commands>(new S());
    commands["W"] = unique_ptr<Commands>(new W());
    commands["E"] = unique_ptr<Commands>(new E());
    commands["get"] = unique_ptr<Commands>(new Get());
    commands["drop"] = unique_ptr<Commands>(new Drop());
    commands["open"] = unique_ptr<Commands>(new Open());
    commands["eat"] = unique_ptr<Commands>(new Eat());
    commands["help"] = unique_ptr<Commands>(new Help());
    commands["exit"] = unique_ptr<Commands>(new Exit());

    model->createStandardEvent();
}

bool Controller::process(string str) {
    string str1;
    stringstream ins(str);
    getline(ins, str1, ins.widen(' '));
    if(commands.find(str1) != commands.end()) {
        commands[str1]->perform(str);
    }else model->createCommandErrorEvent();
    if(exitCode)
        return true;
    return false;
}


void Controller::playerWin() {
    model->createWinEvent();
    exitCode = true;
}

void Controller::playerLose() {
    model->createLoseEvent();
    exitCode = true;
}


Items Controller::stringToItem(string s) {
    if (s == "key") {
        return key;
    }
    if (s == "food") {
        return food;
    }
    if (s == "torchlight") {
        return torchlight;
    }
    if (s == "chest") {
        return chest;
    }
    return none;
}

bool Controller::isSeeAnything() {
    if(model->field[model->player->x][model->player->y].darkroom){
        for(Items Item: model->field[model->player->x][model->player->y].items)
            if(Item == torchlight){
                return true;
            }
        for(Items Item: model->player->items)
            if(Item == torchlight){
                return true;
            }
    } else return true;
    return false;
}

//Controller does some manipulations with model and tells which event model must create
void Controller::N::perform(string s) {
    if (model->field[model->player->x][model->player->y].Top == Close){
        model->createMoveErrorEvent();
    } else {
        -- model->player->y;
        -- model->player->steps;
        if(model->player->steps < 0){
            playerLose();
            return;
        }
        if(isSeeAnything()){
            model->createStandardEvent();
        }else model->createDarkroomEvent();
    }
}

void Controller::E::perform(string s) {
    if(model->field[model->player->x][model->player->y].Right == Close){
        model->createMoveErrorEvent();
    } else {
        ++ model->player->x;
        -- model->player->steps;
        if(model->player->steps < 0){
            playerLose();
            return;
        }
        if(isSeeAnything()){
            model->createStandardEvent();
        }else model->createDarkroomEvent();
    }
}

void Controller::S::perform(string s) {
    if(model->field[model->player->x][model->player->y].Bottom == Close){
        model->createMoveErrorEvent();
    } else {
        ++ model->player->y;
        -- model->player->steps;
        if(model->player->steps < 0){
            playerLose();
            return;
        }
        if(isSeeAnything()){
            model->createStandardEvent();
        }else model->createDarkroomEvent();
    }
}

void Controller::W::perform(string s) {
    if(model->field[model->player->x][model->player->y].Left == Close){
        model->createMoveErrorEvent();
    } else {
        -- model->player->x;
        -- model->player->steps;
        if(model->player->steps < 0){
            playerLose();
            return;
        }
        if(isSeeAnything()){
            model->createStandardEvent();
        }else model->createDarkroomEvent();
    }
}

void Controller::Get::perform(string s) {
    if(isSeeAnything()) {
        size_t t = s.find_first_of(' ');
        if (t > 0) {
            string str(s.begin() + s.find_first_of(' ') + 1, s.end());
            Items item = stringToItem(str);
            if (item != chest && item != none) {
                for (int i = 0; i < model->field[model->player->x][model->player->y].items.size(); ++i) {
                    if (item == model->field[model->player->x][model->player->y].items[i]) {
                        try {
                            model->player->items.push_back(item);
                            model->field[model->player->x][model->player->y].items.erase(
                                    model->field[model->player->x][model->player->y].items.begin() + i);
                            model->createStandardEvent();
                            return;
                        } catch (const exception &) {
                            model->createBadErrorEvent();
                            return;
                        }
                    }
                }
            }
        }
        model->createGetErrorEvent();
        return;
    } model->createDarkroomEvent();
}

void Controller::Drop::perform(string s) {
    if(isSeeAnything()) {
        size_t t = s.find_first_of(' ');
        if (t > 0) {
            string str(s.begin() + s.find_first_of(' ') + 1, s.end());
            Items item = stringToItem(str);
            if (item != chest && item != none) {
                for (int i = 0; i < model->player->items.size(); ++i) {
                    if (item == (model->player->items[i])) {
                        try {
                            model->field[model->player->x][model->player->y].items.push_back(item);
                            model->player->items.erase(model->player->items.begin() + i);
                            model->createStandardEvent();
                            return;
                        } catch (const exception &) {
                            model->createBadErrorEvent();
                            return;
                        }
                    }
                }
            }
        }
        model->createDropErrorEvent();
    }  model->createDropErrorEvent();
}

void Controller::Eat::perform(string s) {
    if(isSeeAnything()) {
        size_t t = s.find_first_of(' ');
        if (t > 0) {
            string str(s.begin() + s.find_first_of(' ') + 1, s.end());
            Items item = stringToItem(str);
            if (item == food) {
                for (int i = 0; i < model->field[model->player->x][model->player->y].items.size(); ++i) {
                    if (item == model->field[model->player->x][model->player->y].items[i]) {
                        try {
                            model->player->steps += (int)(model->getInitialCountOfSteps() * 0.15);
                            model->field[model->player->x][model->player->y].items.erase(
                                    model->field[model->player->x][model->player->y].items.begin() + i);
                            model->createEatEvent();
                            model->createStandardEvent();
                            return;
                        } catch (const exception &) {
                            model->createBadErrorEvent();
                            return;
                        }
                    }
                }
            }
        }
        model->createEatErrorEvent();
        return;
    } model->createDarkroomEvent();
}

void Controller::Open::perform(string s) {
    if(isSeeAnything()) {
        size_t t = s.find_first_of(' ');
        if (t > 0) {
            string str(s.begin() + s.find_first_of(' ') + 1, s.end());
            Items item = stringToItem(str);
            if (item == chest) {
                for (Items Item : model->player->items) {
                    if (Item == key) {
                        playerWin();
                        return;
                    }
                }
                model->createNoKeyEvent();
                return;
            }
        }
        model->createOpenErrorEvent();
        return;
    }  model->createDarkroomEvent();
}

void Controller::Help::perform(string s) {
    model->createHelpEvent();
}

void Controller::Exit::perform(string s) {
    exitCode = true;
}