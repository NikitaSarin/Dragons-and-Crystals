//
// Created by nikita on 10/28/17.
//

#ifndef DRAGONS_CRYSTALS_MODEL_H
#define DRAGONS_CRYSTALS_MODEL_H

#include <iostream>
#include <vector>
#include "View.h"
#include "Room.h"
#include "Player.h"

using namespace std;

class Model {
private:
    int width = 0;
    int height = 0;
    vector<View* > subscribedModels;

    void createLabyrinth();
    void createKeyAndChest();
    void locateItem(int *x, int *y, int steps);
    void createDarkroom();
    void randomLocateItem(Items item);
public:
    Model(int m, int n);
    static Room **field;
    static Player *player;
    void printLabyrinth();

    void createStandardEvent();
    void createDarkroomEvent();
    void createEatEvent();
    void createHelpEvent();

    void createMoveErrorEvent();
    void createGetErrorEvent();
    void createDropErrorEvent();
    void createEatErrorEvent();
    void createCommandErrorEvent();
    void createOpenErrorEvent();
    void createNoKeyEvent();
    void createBadErrorEvent();

    void createWinEvent();
    void createLoseEvent();

    void notifyViews(Event *e);
    bool subscribe(View* view);

    int getInitialCountOfSteps();
~Model();
};


#endif //DRAGONS_CRYSTALS_MODEL_H
