//
// Created by nikita on 10/28/17.
//

#include <cstdlib>
#include "Model.h"
#include <stack>
#include <cmath>

using namespace std;

//   N
// W   E
//   S

Model::Model(int m, int n) {
    width = n;
    height = m;
    field = new Room*[n];
    for (int i = 0; i < width; ++i) {
        field[i] = new Room[m];
    }
    srand(time(NULL));
    createLabyrinth();
    player = new Player(rand()%n, rand()%m, m*n);
    createKeyAndChest();
    createDarkroom();
    randomLocateItem(torchlight);
    for (int j = 0; j < (int)(sqrt(width * height)/3); ++j) {
        randomLocateItem(food);
    }
}

bool Model::subscribe(View* view) {
    subscribedModels.push_back(view);
} // Views can subscribe to model updates

void Model::notifyViews(Event e) {
    for (auto& v: subscribedModels) {
        v->update(e);
    }
} // Model creates some event and notifies views

//Normal events

void Model::createWinEvent() {
    notifyViews(Event(win, OK));
}

void Model::createLoseEvent() {
    notifyViews(Event(lose, OK));
}

void Model::createStandardEvent() { // Prepare information for transmission to Views
    vector<char> doors;
    vector<Items> roomItems;
    vector<Items> playerItems;
    try {
        if (field[player->x][player->y].Top == Open)
            doors.push_back('N');
        if (field[player->x][player->y].Right == Open)
            doors.push_back('E');
        if (field[player->x][player->y].Bottom == Open)
            doors.push_back('S');
        if (field[player->x][player->y].Left == Open)
            doors.push_back('W');

        for (Items item : player->items) {
            playerItems.push_back(item);
        }
        for (Items item : field[player->x][player->y].items) {
            roomItems.push_back(item);
        }
    }  catch (const exception &){
        return createBadErrorEvent();
    }
    notifyViews(Event(standard, player->x, player->y, player->steps, playerItems, roomItems,
                       doors, OK));
}

void Model::createDarkroomEvent() {
    notifyViews(Event(darkRoom, OK));
}

void Model::createHelpEvent() {
    notifyViews(Event(help, OK));
}

void Model::createEatEvent() {
    notifyViews(Event(eat, OK));
}

//Error events

void Model::createCommandErrorEvent() {
    notifyViews(Event(ERROR, CommandError));
}

void Model::createMoveErrorEvent() {
    notifyViews(Event(ERROR, MoveError));
}

void Model::createGetErrorEvent() {
    notifyViews(Event(ERROR, GetError));
}

void Model::createDropErrorEvent() {
    notifyViews(Event(ERROR, DropError));
}

void Model::createEatErrorEvent() {
    notifyViews(Event(ERROR, EatError));
}

void Model::createOpenErrorEvent() {
    notifyViews(Event(ERROR, OpenError));
}

void Model::createNoKeyEvent() {
    notifyViews(Event(ERROR, NoKey));
}

void Model::createBadErrorEvent() {
    notifyViews(Event(ERROR, BIGERROR));
} //If something goes wrong (exceptions)


void Model::createDarkroom() {
    srand(time(NULL));
    int x, y;
    for (int i = 0; i < (int)(height*width*0.3); ++i) {
        x = rand() % width;
        y = rand() % height;
        while(x == player->x && y == player->y){
            x = rand() % width;
            y = rand() % height;
        }
        field[x][y].darkroom = true;
    }
} //Transform random rooms to darkrooms

void Model::locateItem(int *x, int *y, int steps) {
    unsigned long dir;
    //fill in the initial data for rooms
    stack<Room> path;
    path.push(field[*x][*y]);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            field[j][i].Visited = false;
        }

    for (int k = 0; k < steps; ++k) {
        Room room = path.top();
        //put room in path and start building the path
        vector<Room> nextStep;
        field[room.x][room.y].Visited = true;
        if (room.Left == Open && !field[room.x - 1][room.y].Visited)
            nextStep.push_back(field[room.x - 1][room.y]);
        if (room.Right == Open && !field[room.x + 1][room.y].Visited)
            nextStep.push_back(field[room.x + 1][room.y]);
        if (room.Top == Open && !field[room.x][room.y - 1].Visited)
            nextStep.push_back(field[room.x][room.y - 1]);
        if (room.Bottom == Open && !field[room.x][room.y + 1].Visited)
            nextStep.push_back(field[room.x][room.y + 1]);

        if (!nextStep.empty()) {
            //choose direction from variants
            dir = rand() % nextStep.size();
            Room next = nextStep[dir];
            nextStep.erase(nextStep.begin() + dir);
            path.push(next);
        }
        else {
            path.pop();
        }
    }
    *x = path.top().x;
    *y = path.top().y;
} //The item is located within 'steps' from the player

void Model::randomLocateItem(Items item) {
    srand(time(NULL));
    field[rand() % width][rand() % height].items.push_back(item);
}

void Model::createKeyAndChest() {
    auto x = new int((*player).x);
    auto y = new int((*player).y);
    locateItem(x, y, (int) (height * width * 0.2));
    field[*x][*y].items.push_back(key);
    locateItem(x, y, (int) (height * width * 0.3));
    field[*x][*y].items.push_back(chest);
    delete x;
    delete y;
}

void Model::createLabyrinth() {
    //fill in the initial data for rooms
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            field[x][y].x = x;
            field[x][y].y = y;
        }

    //choose first room
    int startX = rand() % width;
    int startY = rand() % height;

    field[startX][startY].Visited = true;

    //put room in path and start building the path
    stack<Room> path;
    path.push(field[startX][startY]);

    while (!path.empty())
    {
        Room room = path.top();

        //check variants
        vector<Room> nextStep;
        if (room.x > 0 && (!field[room.x - 1][room.y].Visited))
            nextStep.push_back(field[room.x - 1][room.y]);
        if (room.x < width - 1 && (!field[room.x + 1][room.y].Visited))
            nextStep.push_back(field[room.x + 1][room.y]);
        if (room.y > 0 && (!field[room.x][room.y - 1].Visited))
            nextStep.push_back(field[room.x][room.y - 1]);
        if (room.y < height - 1 && (!field[room.x][room.y + 1].Visited))
            nextStep.push_back(field[room.x][room.y + 1]);

        if (!nextStep.empty())
        {
            //choose direction from variants
            Room next = nextStep[rand() % nextStep.size()];

            //open doors
            if (next.x != room.x)
            {
                if (room.x - next.x > 0)
                {
                    field[room.x][room.y].Left = Open;
                    field[next.x][next.y].Right = Open;
                }
                else
                {
                    field[room.x][room.y].Right = Open;
                    field[next.x][next.y].Left = Open;
                }
            }
            if (next.y != room.y)
            {
                if (room.y - next.y > 0)
                {
                    field[room.x][room.y].Top = Open;
                    field[next.x][next.y].Bottom = Open;
                }
                else
                {
                    field[room.x][room.y].Bottom = Open;
                    field[next.x][next.y].Top = Open;
                }
            }

            field[next.x][next.y].Visited = true;
            path.push(next);

        }
        else
        {
            //return to the last variant
            path.pop();
        }
    }
}

void Model::printLabyrinth() {
    for (int j = 0; j < width; ++j) {
        cout << " _";
    }
    cout << endl;
    for (int k = 0; k < height; ++k) {
        for (int i = 0; i < width; ++i) {
                if (field[i][k].Left == Close) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            if(i == (*player).x && k == (*player).y){
                if(field[i][k].Bottom == Close)
                    cout << "P";
                else cout << "p";
            } else {
                if (field[i][k].items.size() > 0) {
                    if (field[i][k].items[0] == chest) {
                        if (field[i][k].Bottom == Close)
                            cout << "C";
                        else cout << "c";
                    } else {
                        if (field[i][k].items[0] == key) {
                            if (field[i][k].Bottom == Close)
                                cout << "K";
                            else cout << "k";
                        }
                    }
                } else {
                    if (field[i][k].Bottom == Close) {
                        cout << "_";
                    } else {
                        cout << " ";
                    }
                }
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}// Debug function

int Model::getInitialCountOfSteps() {
    return width * height;
} // Return initial count of steps

Model::~Model() {
    for (int i = 0; i < width; ++i) {
        delete[] field[i];
    }
    delete[] field;
    delete player;
}