#pragma once

#include "../Entity.hpp"
#include <string>
#include "../../../AbstractionLayer/OtherInterfaces/UserInputManagerInterface.hpp"

enum MovementDirection {
    LEFT,
    RIGHT,
    STATIONARY
};

class Player : public Entity {
public:
    Player(ResourceManagerInterface* resourceMan);
    ~Player();
    
    void update() override;
    void render(VisualRendererInterface* renderer) override;

    void moveLeft();
    void moveRight();
    void setMovementDirection(MovementDirection direction);
    
    void kill();
    int getShootCooldown();
    void resetShootCooldown();
    
    void setShooting(bool shooting);
    bool isShooting();

    void setHoldShootDown(bool hold);
    bool isHoldShootDown() const;

private:
    bool shooting;
    bool dying;
    bool holdShootDownFlag;
    MovementDirection direction;
    int shootCooldown;
    ImageInfo* currentRenderedImage;
    ImageInfo* deathImageFrame0;
    ImageInfo* deathImageFrame1;
    int deathAnimationCounter;
    bool deathAnimationToggle;
};
