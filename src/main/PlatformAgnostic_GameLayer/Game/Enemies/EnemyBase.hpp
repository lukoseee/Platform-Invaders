#pragma once

#include "../Entity.hpp"

/*
 Base class to generalise all common behaviour between classes: Enemy and RedEnemy
 */
class EnemyBase : public Entity {
public:
    EnemyBase();
    virtual ~EnemyBase() = default;
    void update() override;
    void render(VisualRendererInterface* renderer) override;
    
    int getExplosionCounter();
    bool isDying();
    void kill();
    
protected:
    ImageInfo* currentRenderedImage;
    bool dying;
    int explosionCounter;
};
