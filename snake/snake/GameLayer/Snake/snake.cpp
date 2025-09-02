#include "snake.hpp"

Snake::Snake(Renderer* renderer, ResourceManagerInterface* resourceManager, int length, Direction dir) {
    this->renderer = renderer;
    this->resourceManager = resourceManager;
    this->length = length;
    this->dir = dir;
    
    state = ALIVE;
    deathFrameCounter = 0;
}

Snake::~Snake() {
    // Remove and delete all images associated with the snake's body
    for (auto& segment : body) {
        if (segment.second) {
            renderer->remove(segment.second);
            delete segment.second;
        }
    }
    while(!dirQ.empty())
        dirQ.pop();
    while(!body.empty())
        body.pop_back();
}

void Snake::initalise(Position root) {
    for(int i = 0; i < length; i++) {
        Position pos = {(float) root.x + i, (float) root.y};
        ImageInfo* img;
        if(i == length - 1) {
            img = getHeadImg();
        } else {
            img = getBodyImg();
        }
        renderer->render(img, pos);
        body.push_front({pos, img});
    }
}

void Snake::update() {
    switch(state) {
        case ALIVE:
            move();
            break;
        case DYING:
            playDeath();
            break;
        case DEAD:
            break;
    }
}

void Snake::changeDirection(Direction newDir) {
    // sanity checks to enforce user to not immediatly die due to 'fat-fingering keys'
    if(dirQ.empty() && oppositeDirs(dir, newDir))
        return;
    if(!dirQ.empty() && oppositeDirs(newDir, dirQ.front()))
       return;
       
    dirQ.push(newDir);
}

bool Snake::colliding(Position pos) {
    for (auto it = body.begin(); it != body.end(); it++) {
        if (it->first == pos) {
            return true;
        }
    }
    return false;
}

bool Snake::selfColliding() {
    Position head = body.front().first;
    
    for (auto it = std::next(body.begin()); it != body.end(); it++) {
        if (it->first == head)
            return true;
    }
    return false;
}

void Snake::incLength() {
    length++;
}

Position Snake::getHeadPos() {
    return body.front().first;
}

SnakeState Snake::getState() {
    return state;
}

void Snake::setState(SnakeState state) {
    this->state = state;
}

void Snake::updateBodyImgs(std::string path) {
    for(auto& elem : body) {
        renderer->remove(elem.second);
        delete elem.second;
        elem.second = nullptr;
        
        elem.second = resourceManager->makeImage(path, CELL_SIZE, CELL_SIZE, true);;
        renderer->render(elem.second, elem.first);
    }
}

void Snake::move() {
    // remove the back of the snake if needed
    if(body.size() == length) {
        ImageInfo* back = body.back().second;
        body.pop_back();
        
        renderer->remove(back);
        delete back;
    }
    
    // change direction if needed
    if(!dirQ.empty()) {
        dir = dirQ.front();
        dirQ.pop();
    }
    
    // render new head of snake
    Position newHeadPos = body.front().first;
    switch(dir) {
        case UP:
            newHeadPos.y++;
            break;
        case DOWN:
            newHeadPos.y--;
            break;
        case LEFT:
            newHeadPos.x--;
            break;
        case RIGHT:
            newHeadPos.x++;
            break;
    }
    
    ImageInfo* img = getHeadImg();
    renderer->render(img, newHeadPos);
    
    // alter 2nd elemnt in body to be a 'body' sprite, not a 'head' sprite
    auto it = body.begin();
    renderer->remove(it->second);
    delete it->second;
    it->second = getBodyImg();
    renderer->render(it->second, it->first);
    
    body.push_front({newHeadPos, img});
}

void Snake::playDeath() {
    deathFrameCounter++;
    
    std::string path;
    switch(deathFrameCounter) {
        case 1:
            renderer->remove(body.front().second);
            delete body.front().second;
            body.pop_front();
            path = SNAKE_DEATH_PATH_ONE;
            break;
        case 2:
            path = SNAKE_DEATH_PATH_TWO;
            break;
        case 3:
            path = SNAKE_DEATH_PATH_THREE;
            break;
        case 4:
            state = DEAD;
            for(auto elem : body) {
                renderer->remove(elem.second);
                delete elem.second;
            }
            body.clear();
            return;
    }
    updateBodyImgs(path);
}

// selects and returns the correct snake head image based upon the player direction
ImageInfo* Snake::getHeadImg() {
    std::string path;
    switch(dir) {
        case UP: path = SNAKE_HEAD_UP; break;
        case LEFT: path = SNAKE_HEAD_LEFT; break;
        case DOWN: path = SNAKE_HEAD_DOWN; break;
        case RIGHT: path = SNAKE_HEAD_RIGHT; break;
    }
    return resourceManager->makeImage(path, CELL_SIZE, CELL_SIZE, true);
}

// selects and returns the correct snake head image based upon the player direction
ImageInfo* Snake::getBodyImg() {
    std::string path;
    switch(dir) {
        case UP: path = SNAKE_BODY_UP; break;
        case LEFT: path = SNAKE_BODY_LEFT; break;
        case DOWN: path = SNAKE_BODY_DOWN; break;
        case RIGHT: path = SNAKE_BODY_RIGHT; break;
    }
    return resourceManager->makeImage(path, CELL_SIZE, CELL_SIZE, true);
}
