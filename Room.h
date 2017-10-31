//
// Created by nikita on 10/29/17.
//

#ifndef DRAGONS_CRYSTALS_ROOM_H
#define DRAGONS_CRYSTALS_ROOM_H

#include <iostream>
#include <vector>

enum DoorState { Close, Open };

class Room{
public:
    int x = 0;
    int y = 0;
    DoorState Left = Close;
    DoorState Right = Close;
    DoorState Top = Close;
    DoorState Bottom = Close;
    vector<Items> items = vector<Items>();
    bool darkroom = false;
    bool Visited = false;
    Room() = default;
};

#endif //DRAGONS_CRYSTALS_ROOM_H
