//
// Created by nikita on 10/28/17.
//

#ifndef DRAGONS_CRYSTALS_TEXTVIEW_H
#define DRAGONS_CRYSTALS_TEXTVIEW_H

using namespace std;

#include "View.h"
#include <iostream>
#include <vector>

class TextView: public View {
private:
    void standardEvent(Event e);
public:
    void update(Event e) override;
};


#endif //DRAGONS_CRYSTALS_TEXTVIEW_H
