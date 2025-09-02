#pragma once

#include "Entity.hpp"
#include "GameController.hpp"

class VisualRendererInterface;

class Paddle : public Entity {
public:
    Paddle(float startX, float startY , float speed);
    virtual ~Paddle();

    void update() override;
    void handleInput(const std::string& input) override;
    void render(VisualRendererInterface* renderer) override;

    void moveUp();
    void moveDown();
    void setState(GameState);

private:
    float speed;
    GameState state;
};