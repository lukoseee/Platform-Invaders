#pragma once

#include <queue>
#include <utility>
#include <list>

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

enum SnakeState {
    ALIVE,
    DYING,
    DEAD
};

class Snake {
public:
    Snake(Renderer*, ResourceManagerInterface*, int, Direction);
    ~Snake();
    
    void initalise(Position);
    void update();
    void changeDirection(Direction);
    bool colliding(Position);
    bool selfColliding();
    void incLength();
    Position getHeadPos();
    SnakeState getState();
    void setState(SnakeState);
    
private:
    void updateBodyImgs(std::string);
    void move();
    void playDeath();
    ImageInfo* getHeadImg();
    ImageInfo* getBodyImg();
    
    ImageInfo* img;
    Renderer* renderer;
    ResourceManagerInterface* resourceManager;
    int length;
    Direction dir;
    std::queue<Direction> dirQ;
    std::list<std::pair<Position, ImageInfo*>> body;
    SnakeState state;
    int deathFrameCounter;
};
