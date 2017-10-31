//
// Created by nikita on 10/30/17.
//

#ifndef DRAGONS_CRYSTALS_FACTORY_H
#define DRAGONS_CRYSTALS_FACTORY_H


#include "Controller.h"
#include "TextView.h"

class Factory {
private:
    Factory();
    Controller* controller;
    Model* model;
    TextView* textview;
public:
    Factory(Factory const&) = delete;
    Factory& operator=(Factory const&) = delete;
    static Factory & getFactory();
    bool process();
    ~Factory();
};


#endif //DRAGONS_CRYSTALS_FACTORY_H
