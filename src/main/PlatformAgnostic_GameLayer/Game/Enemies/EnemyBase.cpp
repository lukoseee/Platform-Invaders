#include "EnemyBase.hpp"

EnemyBase::EnemyBase() {
    dying = false;
    explosionCounter = 0;
    currentRenderedImage = nullptr;
}

void EnemyBase::update() {
    if(dying) {
        explosionCounter++;
    }
}

void EnemyBase::render(VisualRendererInterface* renderer) {
    if(currentRenderedImage == image) {
        renderer->moveRenderedImage(getImage(), getPosition().x, getPosition().y);
        return;
    }
    
    renderer->removeImage(currentRenderedImage);
    renderer->renderImage(image, getPosition().x, getPosition().y);
    currentRenderedImage = image;
}

int EnemyBase::getExplosionCounter() {
    return explosionCounter;
}

bool EnemyBase::isDying() {
    return dying;
}

void EnemyBase::kill() {
    dying = true;
}

