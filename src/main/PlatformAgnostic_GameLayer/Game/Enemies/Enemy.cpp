#include "Enemy.hpp"
#include "../../Constants.hpp"
#include <random>

// Constructor that DOES take a PlatformInterface pointer (for audio, etc.).
Enemy::Enemy(int startX, int startY, ImageInfo* img0, ImageInfo* img1)
{
    imageFrame0 = img0;
    imageFrame1 = img1;
    image = imageFrame0;
    animationToggle = false;
    animationCounter = 0;
    resetShootCooldown();
    pos = {startX, startY};
}

Enemy::~Enemy()
{
    if(image != imageFrame0 && image != imageFrame1)
        delete image;
    
    delete imageFrame0;
    delete imageFrame1;
}

void Enemy::update()
{
    shootCooldown--;
    
    // Check if the enemy is dead.
    if(!dying) {
        animationCounter++;
        // Animate between frames.
        if (animationCounter >= ENEMY_ANIMATION_THRESHOLD) {
            animationToggle = !animationToggle;
            image = animationToggle ? imageFrame1 : imageFrame0;
            animationCounter = 0;
        }
    }
    EnemyBase::update();
}

int Enemy::getShootCooldown()
{
    return shootCooldown;
}

void Enemy::resetShootCooldown()
{
    shootCooldown = rand() % ENEMY_SHOOT_COOLDOWN_RANGE + ENEMY_SHOOT_COOLDOWN_MIN;
}
