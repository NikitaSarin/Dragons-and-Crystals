//
// Created by nikita on 10/30/17.
//

#ifndef DRAGONS_CRYSTALS_FACTORY_H
#define DRAGONS_CRYSTALS_FACTORY_H


#include "Controller.h"
#include "TextView.h"

class Factory {
private:
    static Factory instance;
    Factory();
    Controller* controller;
    Model* model;
    TextView* textview;
public:
    static Factory & getFactory();
    bool process();
    ~Factory();
};


#endif //DRAGONS_CRYSTALS_FACTORY_H
