//
// Created by nikita on 10/28/17.
//
#include <iostream>
#include "Event.h"

#ifndef DRAGONS_CRYSTALS_COMMANDS_H
#define DRAGONS_CRYSTALS_COMMANDS_H

using namespace std;

class Commands{
public:
    virtual void perform(string s) = 0;
};

#endif //DRAGONS_CRYSTALS_COMMANDS_H
