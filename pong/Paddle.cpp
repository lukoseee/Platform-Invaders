#include "Paddle.hpp"
#include "Library/AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp""

Paddle::Paddle(float startX, float startY, float s)
{
    pos = { startX, startY };
    speed = s;
    image = nullptr;
    state = GameState::STATIONARY;
}

Paddle::~Paddle() {}

void Paddle::update()
{
    switch (state) {
        case GameState::UP: moveUp(); break;
        case GameState::DOWN: moveDown(); break;
        default: break;
    }

}

void Paddle::handleInput(const std::string& input)
{
    
}

void Paddle::render(VisualRendererInterface* renderer)
{
    if (image && renderer)
        renderer->moveRenderedImage(image, pos.x, pos.y);
}

void Paddle::moveUp()
{   
    pos.y += speed;
}

void Paddle::moveDown()
{
    pos.y -= speed;
}

void Paddle::setState(GameState state) {
    this->state = state;
}