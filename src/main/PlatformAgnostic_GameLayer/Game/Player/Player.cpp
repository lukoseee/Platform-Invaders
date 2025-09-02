#include "Player.hpp"
#include "../../../AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"
#include "../../Constants.hpp"

// Constructor: Initialize movement, shooting, death animation, and lives.
Player::Player(ResourceManagerInterface* resourceMan)
{
    image = resourceMan->makeImage(PLAYER_IMAGE, PLAYER_WIDTH, PLAYER_HEIGHT, true);
    deathImageFrame0 = resourceMan->makeImage("0_player_death", PLAYER_DEATH_WIDTH, PLAYER_DEATH_HEIGHT, true);
    deathImageFrame1 = resourceMan->makeImage("1_player_death", PLAYER_DEATH_WIDTH, PLAYER_DEATH_HEIGHT, true);
    currentRenderedImage = nullptr;
    
    pos = {PLAYER_START_X, PLAYER_START_Y};
    
    deathAnimationToggle = false;
    deathAnimationCounter = 0;
    dying = false;
    direction = STATIONARY;
    holdShootDownFlag = false;
    
    resetShootCooldown();
}

Player::~Player()
{

    // only delete `image` if it isn’t one of the death‐frames
    if (image != deathImageFrame0 && image != deathImageFrame1) {
        delete image;
    }
    
    delete deathImageFrame0;
    delete deathImageFrame1;
}

void Player::moveLeft()
{
    if(pos.x > 0)
        pos.x -= PLAYER_MOVE_DISTANCE;
}

void Player::moveRight()
{
    if(pos.x + image->getWidth() < WINDOW_WIDTH)
        pos.x += PLAYER_MOVE_DISTANCE;
}

void Player::kill() {
    dying = true;
    delete image;
    image = deathImageFrame0;
}

void Player::update()
{
    if(dying) {
        // Toggle between death frames at intervals defined by deathAnimationThreshold.
        if (deathAnimationCounter % PLAYER_DEATH_ANIMATION_THRESHOLD == 0) {
            deathAnimationToggle = !deathAnimationToggle;
            image = deathAnimationToggle ? deathImageFrame1 : deathImageFrame0;
        }
    
        deathAnimationCounter++;
        return;
    }
    
    shootCooldown--;
    switch(direction) {
        case LEFT: moveLeft(); break;
        case RIGHT: moveRight(); break;
        default: break;
    }
}

void Player::render(VisualRendererInterface* renderer)
{
    if(currentRenderedImage == image) {
        renderer->moveRenderedImage(getImage(), getPosition().x, getPosition().y);
        return;
    }
    
    renderer->removeImage(currentRenderedImage);
    renderer->renderImage(image, getPosition().x, getPosition().y);
    currentRenderedImage = image;
}

void Player::setMovementDirection(MovementDirection direction) {
    this->direction = direction;
}

int Player::getShootCooldown() {
    return shootCooldown;
}

void Player::resetShootCooldown() {
    shootCooldown = PLAYER_SHOOT_COOLDOWN;
}

void Player::setShooting(bool shooting) {
    this->shooting = shooting;
}
bool Player::isShooting() {
    return shooting;
}

void Player::setHoldShootDown(bool hold) {
    holdShootDownFlag = hold;
}

bool Player::isHoldShootDown() const {
    return holdShootDownFlag;
}