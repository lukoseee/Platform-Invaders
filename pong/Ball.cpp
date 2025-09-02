#include "Ball.hpp"
#include "Library/AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"


Ball::Ball(float startX, float startY)
{
    pos = { startX, startY };
    velocity = { 0 , 0 };
    image = nullptr;
}

Ball::~Ball() {}

void Ball::update()
{
    pos.x += velocity.x;
    pos.y += velocity.y;
}

void Ball::render(VisualRendererInterface* renderer)
{
    if (image && renderer)
        renderer->moveRenderedImage(image, pos.x, pos.y);
}

void Ball::bounceVertical()
{
	velocity.y *= -1.1f;
}

void Ball::bounceHorizontal()
{
	velocity.x *= -1;
}

void Ball::handleInput(const std::string& input) {
    void();
}
