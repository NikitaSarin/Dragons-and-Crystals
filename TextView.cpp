//
// Created by nikita on 10/28/17.
//

#include "TextView.h"

void TextView::standardEvent(Event e) {
    cout << "You have left " << e.getSteps() << " steps" << endl
         << "You have " << e.getPlayerItems().size() << " items:";
    for (Items item : e.getPlayerItems()) {
        cout << " " << item;
    }
    cout << endl;
        cout << "You are in the room ["<< e.getX() << "," << e.getY() << "]." << endl
         << "There are " << e.getDoors().size() << " doors:";
    for (char door : e.getDoors()) {
        cout << " " << door;
    }
    cout << "." << endl << "Items in the room:";
    for (Items item : e.getRoomItems()) {
        cout << " " << item;
    }
    cout << endl;
}

void TextView::update(Event e) {
    switch (e.getCode()){
        case OK:{ break;}
        case GetError:{
            cout << "Can't get this item!" << endl;
            return;
        }
        case DropError:{
            cout << "Can't drop this item!" << endl;
            return;
        }
        case MoveError:{
            cout << "Can't move in this direction!" << endl;
            return;
        } case CommandError:{
            cout << "Bad command! Use 'help' to get help!" << endl;
            return;
        }
        case OpenError:{
            cout << "Can't open this item!" << endl;
            return;
        }
        case NoKey:{
            cout << "You haven't key for the chest!" << endl;
            return;
        }
        default:{
            cout << "BAD ERROR CODE. FLY, YOU FOOLS." << endl;
            return;
        }
    }
    switch (e.getName()){
        case standard:{
            standardEvent(e);
            break;
        }
        case monsterAttack:{
            break;
        }
        case darkRoom:{
            for (Items item : e.getRoomItems()) {
                if(item == torchlight){
                    standardEvent(e);
                    return;
                }
            }
            for (Items item : e.getPlayerItems()) {
                if(item == torchlight){
                    standardEvent(e);
                    return;
                }
            }
            cout << "Can’t see anything in this dark place!" << endl;
            break;
        }
        case win:{
            cout << "YOU WIN! Congratulations!" << endl;
            break;
        }
        case lose:{
            cout << "You lose :( Don't worry, try again!" << endl;
            break;
        }
        case help:{
            cout << "Use 'N' to move in the N direction\n"
                    "Use 'E' to move in the E direction\n"
                    "Use 'S' to move in the S direction\n"
                    "Use 'W' to move in the W direction\n"
                    "Attention! You can move only in the directions of the doors\n"
                    "Use 'get [item]' to put an item into your backpack\n"
                    "Attention! You can get only items in the current room\n"
                    "Use 'drop [item]' to throw an item away of your backpack\n"
                    "Attention! You can drop only items from your backpack\n"
                    "Use 'eat food' to for the replenishment of vitality\n"
                    "Attention! You can eat only food in the current room\n"
                    "Use 'open chest' to open the chest\n"
                    "Attention! You can open the chest if you have the key\n"
                    "Use 'exit' to exit"<< endl;
            break;
        }
        case eat:{
            cout << "OMNOMNOM!" << endl;
            break;
        }
        default:{
            cout << "BAD EVENT NAME. FLY, YOU FOOLS." << endl;
            return;
        }
    }

}

