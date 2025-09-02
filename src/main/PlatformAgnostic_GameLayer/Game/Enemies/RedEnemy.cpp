#include "RedEnemy.hpp"
#include "../../Constants.hpp"

RedEnemy::RedEnemy(ResourceManagerInterface* resourceMan)
{
    pos = {RED_ENEMY_SPAWN_X, RED_ENEMY_Y};
    image = resourceMan->makeImage(RED_ENEMY_IMAGE, RED_ENEMY_WIDTH, RED_ENEMY_HEIGHT, true);
}

RedEnemy::~RedEnemy()
{
    delete image;
}

void RedEnemy::update()
{
    Position p = getPosition();
    p.x += RED_ENEMY_SPEED;
    setPosition(p);

    // Mark as destroyed if off-screen
    if (getPosition().x > WINDOW_WIDTH + RED_ENEMY_MARGIN) {
        dying = true;
    }
    
    EnemyBase::update();
}

