//
// Created by nikita on 10/30/17.
//

#include <limits>
#include "Factory.h"
#include "TextView.h"

//Factory* Factory::instance = nullptr;//new Factory();
Factory::Factory() {
    int m = 0;
    int n = 0;
    string str;
    cout << "Dragons and Crystals 2017. Push ENTER for continue!";
    getchar();
    textview = new TextView();
    cout << "Enter height and width of the field!" << endl;
    cin >> m >> n;
    while(!cin || (m < 1 || m > 1001 || n < 1 || n > 1001))
    {
        cout << "Please, enter numbers from the range [1;1000]" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> m >> n;
    }
    model = new Model(m, n);
    model->subscribe(textview);
    controller = new Controller(model);
}

Factory & Factory::getFactory() {
    static Factory instance;
    return instance;
}

bool Factory::process() {
    bool exit = false;
    string str;
    while(!exit){
        getline(cin, str);
        if(!str.empty()) {
            exit = controller->process(str);
        }
    }
}

Factory::~Factory() {
    delete controller;
    delete model;
    delete textview;
}

