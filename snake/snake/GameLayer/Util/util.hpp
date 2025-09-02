#pragma once

#include <iostream>

typedef struct Position{
    float x;
    float y;
    
    bool operator == (Position other) {
        return x == other.x && y == other.y;
    }
} Position;

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum GUIState {
    MAIN_MENU,
    GAME,
    LEADERBOARD,
    QUIT
};

enum MenuOption {
    START,
    SCORES,
    MENU_QUIT
};

bool oppositeDirs(Direction, Direction);
int getRand(int, int);
