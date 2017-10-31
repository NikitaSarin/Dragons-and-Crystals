//
// Created by nikita on 10/30/17.
//

#include "Event.h"

Event::Event(Name eventName, ErrorCode errorCode) {
    name = eventName;
    code = errorCode;
}

Event::Event(Name eventName, int X, int Y, int Steps, vector<Items> PlayerItems, vector<Items> RoomItems,
             vector<char> Doors, ErrorCode Code) {
    name = eventName;
    x = X;
    y = Y;
    steps = Steps;
    code  = Code;
    for (char d : Doors) {
        doors.push_back(d);
    }
    for (Items item : PlayerItems) {
        playerItems.push_back(item);
    }
    for (Items item : RoomItems) {
        roomItems.push_back(item);
    }
}

Name Event::getName() {
    return name;
}

int Event::getX() {
    return x;
}

int Event::getY() {
    return y;
}

ErrorCode Event::getCode() {
    return code;
}

vector<char> Event::getDoors() {
    return doors;
}

vector<Items> Event::getPlayerItems() {
    return playerItems;
}

vector<Items> Event::getRoomItems() {
    return roomItems;
}

int Event::getSteps() {
    return steps;
}