#include "BulletManager.hpp"

BulletManager::BulletManager(VisualRendererInterface* visualRenderer, ResourceManagerInterface* resourceMan, AudioRendererInterface* audioRenderer) {
    this->visualRenderer = visualRenderer;
    this->resourceMan = resourceMan;
    this->audioRenderer = audioRenderer;
}

BulletManager::~BulletManager() {
    removeAllBullets();
}

void BulletManager::updateAndRender() {
    updateBulletList(&playerBullets);
    updateBulletList(&enemyBullets);
}

void BulletManager::updateBulletList(std::list<Bullet*>* bullets) {
    // go over all bullets, remove any which are out of bounds,
    // and update&render all remaining ones
    for (auto it = bullets->begin(); it != bullets->end(); ) {
        Bullet* bullet = *it;
        it++;
        
        if(outOfBounds(bullet)) {
            removeBullet(bullet, bullets);
            continue;
        }
        
        bullet->update();
        bullet->render(visualRenderer);
    }
}

bool BulletManager::checkCollisions(Player* player) {
    return colliding(player, &enemyBullets);
}

bool BulletManager::checkCollisions(Shield* shield) {
    return colliding(shield, &enemyBullets) || colliding(shield, &playerBullets);
}

bool BulletManager::checkCollisions(EnemyBase* enemy) {
    return colliding(enemy, &playerBullets);
}

void BulletManager::fireEnemyBullet(Enemy* enemy) {
    Position pos = enemy->getPosition();
    Bullet* bullet = new Bullet(pos.x + BULLET_OFFSET_X,
                                pos.y - BULLET_OFFSET_Y,
                                "enemy");

    bullet->setImageFrame0(resourceMan->makeImage(BULLET_ENEMY_IMAGE_0, BULLET_ENEMY_WIDTH, BULLET_ENEMY_HEIGHT, true));
    bullet->setImageFrame1(resourceMan->makeImage(BULLET_ENEMY_IMAGE_1, BULLET_ENEMY_WIDTH, BULLET_ENEMY_HEIGHT, true));
    bullet->setImage(bullet->getImageFrame0());
    bullet->setCurrentRenderedImage(bullet->getImage());

    visualRenderer->renderImage(bullet->getImage(), bullet->getPosition().x, bullet->getPosition().y);
    enemyBullets.push_back(bullet);
}

void BulletManager::firePlayerBullet(Player* player) {
    Position pos = player->getPosition();
    Bullet* bullet = new Bullet(pos.x + BULLET_OFFSET_X,
                                pos.y + BULLET_OFFSET_Y,
                                "player");
    
    bullet->setImage(resourceMan->makeImage(BULLET_IMAGE, BULLET_WIDTH, BULLET_HEIGHT, true));
    visualRenderer->renderImage(bullet->getImage(), bullet->getPosition().x, bullet->getPosition().y);
    playerBullets.push_back(bullet);
    
    // Play shoot sound.
    AudioInfo* shootAudio = resourceMan->makeAudio(SHOOT_SOUND);
    audioRenderer->playSound(*shootAudio);
    delete shootAudio;
}

void BulletManager::removeAllBullets() {
    for (auto it = playerBullets.begin(); it != playerBullets.end(); ) {
        Bullet* bullet = *it;
        it++;
        removeBullet(bullet, &playerBullets);
    }
    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
        Bullet* bullet = *it;
        it++;
        removeBullet(bullet, &enemyBullets);
    }
}

bool BulletManager::colliding(Entity* entity, std::list<Bullet*>* bullets) {
    // calc enetity bounding box
    int bx1 = entity->getPosition().x;
    int by1 = entity->getPosition().y;
    int bx2 = bx1 + entity->getImage()->getWidth();
    int by2 = by1 + entity->getImage()->getHeight();
    
    for (auto it = bullets->begin(); it != bullets->end(); ) {
        Bullet* bullet = *it;
        it++;
        
        // calc bounding box for given bullet
        int ax1 = bullet->getPosition().x;
        int ay1 = bullet->getPosition().y;
        int ax2 = ax1 + bullet->getImage()->getWidth();
        int ay2 = ay1 + bullet->getImage()->getHeight();
        
        // check overlap
        if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1) {
            // remove bullet if there is a collision
            removeBullet(bullet, bullets);
            return true;;
        }
    }
    
    return false;
}

void BulletManager::removeBullet(Bullet* bullet, std::list<Bullet*>* bullets) {
    bullets->remove(bullet);
    visualRenderer->removeImage(bullet->getImage());
    delete bullet;
}

bool BulletManager::outOfBounds(Bullet* bullet) {
    Position pos = bullet->getPosition();
    if(pos.y > WINDOW_HEIGHT || pos.y < 0)
        return true;
    
    return false;
}
