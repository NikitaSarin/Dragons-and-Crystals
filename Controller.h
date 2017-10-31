//
// Created by nikita on 10/28/17.
//
#include <iostream>
#include <map>
#include "Commands.h"
#include "Model.h"

#ifndef DRAGONS_CRYSTALS_CONTROLLER_H
#define DRAGONS_CRYSTALS_CONTROLLER_H

using namespace std;

class Controller {

private:
    map<string, Commands*> commands;
    static Model* model ;
    static bool exitCode ;

    class N: public Commands{ void perform(string s) override; };
    class S: public Commands{ void perform(string s) override; };
    class W: public Commands{ void perform(string s) override; };
    class E: public Commands{ void perform(string s) override; };
    class Get: public Commands{ void perform(string s) override; };
    class Drop: public Commands{ void perform(string s) override; };
    class Open: public Commands{ void perform(string s) override; };
    class Eat: public Commands{ void perform(string s) override; };
    class Help: public Commands{ void perform(string s) override; };
    class Exit: public Commands{ void perform(string s) override; };

    static void playerWin();
    static void playerLose();

    static bool isSeeAnything();
    static Items stringToItem(string s);
public:
    explicit Controller(Model* m);
    bool process(string str);
};


#endif //DRAGONS_CRYSTALS_CONTROLLER_H
