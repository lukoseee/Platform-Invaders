#include "apple.hpp"

Apple::Apple(Renderer* renderer, ImageInfo* img, Snake* snake) {
    this->renderer = renderer;
    this->img = img;
    this->snake = snake;
}

Apple::~Apple() {
    renderer->remove(img);
    delete img;
    img = nullptr;
}

void Apple::spawn() {
    // remove existing img
    renderer->remove(img);
    
    // render apple at new location
    do {
        pos = {(float) getRand(0, NUM_CELLS - 1), (float) getRand(0, NUM_CELLS - 1)};
    } while(snake->colliding(pos));

    renderer->render(img, pos);
}

Position Apple::getPos() {
    return pos;
}

