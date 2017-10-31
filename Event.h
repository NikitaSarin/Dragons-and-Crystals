//
// Created by nikita on 10/29/17.
//

#ifndef DRAGONS_CRYSTALS_EVENT_H
#define DRAGONS_CRYSTALS_EVENT_H

#include <iostream>
#include <vector>

using namespace std;

enum Name{
    standard,
    monsterAttack,
    darkRoom,
    eat,
    win,
    lose,
    help,
    ERROR
};

enum Items{
    key,
    chest,
    torchlight,
    food,
    sword,
    none
};

enum ErrorCode{
    OK,
    GetError,
    DropError,
    MoveError,
    EatError,
    CommandError,
    OpenError,
    NoKey,
    BIGERROR
};

class Event{
private:
    Name name;
    int x;
    int y;
    int steps;
    vector<char> doors;
    vector<Items> roomItems;
    vector<Items> playerItems;
    ErrorCode code;
public:
    Event(Name eventName, int X, int Y, int Steps, vector<Items> PlayerItems, vector<Items> RoomItems,
              vector<char> Doors, ErrorCode Code);
    Event(Name eventName, ErrorCode code);
    Name getName();
    int getX();
    int getY();
    int getSteps();
    vector<char> getDoors();
    vector<Items> getPlayerItems();
    vector<Items> getRoomItems();
    ErrorCode getCode();
};

inline ostream &operator<<(std::ostream &out, const Items& i) {
    switch(i) {
        case key: return (out << "key");
        case chest: return (out << "chest");
        case torchlight: return (out << "torchlight");
        case sword: return (out << "sword");
        case food: return (out << "food");
        default: return (out);
    }
}
#endif //DRAGONS_CRYSTALS_EVENT_H
