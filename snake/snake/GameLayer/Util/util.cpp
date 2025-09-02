
#include "util.hpp"

#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

bool oppositeDirs(Direction dir1, Direction dir2) {
    if((dir1 == UP && dir2 == DOWN) || (dir1 == DOWN && dir2 == UP))
        return true;
    if((dir1 == LEFT && dir2 == RIGHT) || (dir1 == RIGHT && dir2 == LEFT))
        return true;
    return false;
}

int getRand(int min, int max) {
    return min + std::rand() % ((max - min) + 1);
}

