#pragma once

#include "EnemyBase.hpp"
#include <string>

class Enemy : public EnemyBase {
public:
    Enemy(int startX, int startY, ImageInfo* img0, ImageInfo* img1);
    ~Enemy() override;

    void update() override;
    
    int getShootCooldown();
    void resetShootCooldown();

protected:
    int shootCooldown;
    int animationCounter;
    bool animationToggle;
    ImageInfo* imageFrame0;
    ImageInfo* imageFrame1;
};
