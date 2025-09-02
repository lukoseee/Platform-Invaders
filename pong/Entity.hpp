#pragma once

#include <string>
#include "Library/AbstractionLayer/Util/ImageInfo.hpp"

// Forward declaration of VisualRendererInterface
class VisualRendererInterface;

struct Position {
    float x;
    float y;
};

class Entity {
public:
    Entity();
    virtual ~Entity();

    // Pure virtual methods for entity behavior
    virtual void update() = 0;
    virtual void handleInput(const std::string& input) = 0;

    // Rendering uses VisualRendererInterface
    virtual void render(VisualRendererInterface* renderer) = 0;

    // Position
    Position getPosition() const;
    void setPosition(const Position& pos);

    // Velocity
    Position getVelocity() const;
    void setVelocity(const Position& pos);

    // Health
    int getHealth() const;
    void setHealth(int health);

    // ImageInfo
    ImageInfo* getImage() const;
    void setImage(ImageInfo* img);

protected:
    Position pos;
    Position velocity;
    int health;
    ImageInfo* image;
};
