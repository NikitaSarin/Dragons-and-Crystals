//
// Created by nikita on 10/30/17.
//
#include <iostream>
#include <vector>
#include "Event.h"

#ifndef DRAGONS_CRYSTALS_PLAYER_H
#define DRAGONS_CRYSTALS_PLAYER_H

using namespace std;

class Player {
public:
    int x;
    int y;
    int steps;
    vector<Items> items;
    Player(int X, int Y, int Steps){
        x = X;
        y = Y;
        steps = Steps;
    };
};


#endif //DRAGONS_CRYSTALS_PLAYER_H
