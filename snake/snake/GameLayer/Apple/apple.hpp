#pragma once

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../Snake/snake.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class Apple {
public:
    Apple(Renderer*, ImageInfo*, Snake*);
    ~Apple();
    
    void spawn();
    Position getPos();
    
private:
    Position pos;
    Renderer* renderer;
    ImageInfo* img;
    Snake* snake;
};

