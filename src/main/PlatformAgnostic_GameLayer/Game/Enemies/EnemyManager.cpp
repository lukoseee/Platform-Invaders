#include "EnemyManager.hpp"

EnemyManager::EnemyManager(VisualRendererInterface* visualRenderer, ResourceManagerInterface* resourceMan, AudioRendererInterface* audioRenderer) {
    this->visualRenderer = visualRenderer;
    this->resourceMan = resourceMan;
    this->audioRenderer = audioRenderer;
    redEnemy = nullptr;
    frameCount = 0;
    sfxPtr = 0;
    movementDir = 1;
    enemySpeed = ENEMY_GROUP_SPEED;

    musicFrameCounter   = 0;
    musicFrameThreshold = INITIAL_MUSIC_FRAME_THRESHOLD;
}

EnemyManager::~EnemyManager() {
    for(EnemyBase* enemy : enemies) {
        visualRenderer->removeImage(enemy->getImage());
        delete enemy;
    }
    enemies.clear();
    
    if(redEnemy) {
        visualRenderer->removeImage(redEnemy->getImage());
        delete redEnemy;
        redEnemy = nullptr;
    }
}

void EnemyManager::updateAndRender() {
    // below are three events which should occur at regular intervals
    // 1. playing the music
    // 2. speeding up the enemies
    // 3. spawing the red enemy
    musicFrameCounter++;
    if (musicFrameCounter >= musicFrameThreshold) {
        playSFX();
        musicFrameCounter = 0;
    }
    if(frameCount % SPEED_UP_INTERVAL == 0) {
        enemySpeed *= 1.2;
    }
    if(frameCount % RED_ENEMY_SPAWN_INTERVAL == 0) {
        spawnRedEnemy();
    }
    
    // remove exploded enemies
    for (auto it = dyingEnemies.begin(); it != dyingEnemies.end(); ) {
        EnemyBase* enemy = *it;
        it++;
        
        if(enemy->getExplosionCounter() >= ENEMY_EXPLOSION_DURATION) {
            removeEnemy(enemy);
            
            if(enemy == redEnemy)
                redEnemy = nullptr;
        }
        
    }
    
    // change enemy movement direction whenever they hit the edge
    if(hitEdge()) {
        changeEnemyDirection();
    }
    
    // move all enemies
    for (Enemy* enemy : enemies) {
        Position p = enemy->getPosition();
        p.x += movementDir * enemySpeed;
        enemy->setPosition(p);
    }
    
    // update and render
    for(Enemy* enemy : enemies) {
        enemy->update();
        enemy->render(visualRenderer);
    }
    updateAndRenderRedEnemy();
    
    frameCount++;
}

// process the killing of an enemy, set-up them 'exploding'
void EnemyManager::killEnemy(EnemyBase* enemy) {
    enemy->kill();
    enemy->setImage(resourceMan->makeImage("explosion", ENEMY_WIDTH, ENEMY_HEIGHT, true));
    dyingEnemies.push_back(enemy);
}

// remove an enemy from the screen (once they've done exploding, or otherwise)
void EnemyManager::removeEnemy(EnemyBase* enemyBase) {
    visualRenderer->removeImage(enemyBase->getImage());
    
    if(Enemy* enemy = dynamic_cast<Enemy*>(enemyBase)) {
        enemies.remove(enemy);
    }
    
    dyingEnemies.remove(enemyBase);
    delete enemyBase;
}

bool EnemyManager::enemiesLeft() {
    return !enemies.empty();
}

void EnemyManager::spawnRedEnemy() {
    // play the spawn audio
    AudioInfo* spawnAudio = resourceMan->makeAudio(RED_ENEMY_SPAWN_SOUND);
    audioRenderer->playSound(*spawnAudio);
    delete spawnAudio;
    
    // initalise and render the enemy
    redEnemy = new RedEnemy(resourceMan);
}

// spawn enemies at their inital positions
void EnemyManager::spawnEnemies() {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        int yPos = ENEMY_INITIAL_Y + row * ENEMY_ROW_SPACING;
        
        for (int i = 0; i < ENEMY_PER_ROW; i++) {
            Enemy* enemy;
            
            // configure enemy images based upon the row
            if (row == 0) {
                ImageInfo* img0 = resourceMan->makeImage(ENEMY_IMAGE_FRAME0, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                ImageInfo* img1 = resourceMan->makeImage(ENEMY_IMAGE_FRAME1, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                enemy = new Enemy(ENEMY_INITIAL_X + i * ENEMY_COLUMN_SPACING, yPos, img0, img1);
            } else if (row == 1) {
                ImageInfo* img2 = resourceMan->makeImage(ENEMY_IMAGE_FRAME2, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                ImageInfo* img3 = resourceMan->makeImage(ENEMY_IMAGE_FRAME3, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                enemy = new Enemy(ENEMY_INITIAL_X + i * ENEMY_COLUMN_SPACING, yPos, img2, img3);
            } else {
                ImageInfo* img4 = resourceMan->makeImage(ENEMY_IMAGE_FRAME4, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                ImageInfo* img5 = resourceMan->makeImage(ENEMY_IMAGE_FRAME5, ENEMY_WIDTH, ENEMY_HEIGHT, true);
                enemy = new Enemy(ENEMY_INITIAL_X + i * ENEMY_COLUMN_SPACING, yPos, img4, img5);
            }
            enemies.push_back(enemy);
        }
    }

    //–– speed up the music tick slightly for this new wave ––
    musicFrameThreshold = std::max(
        musicFrameThreshold - MUSIC_THRESHOLD_DECREMENT_PER_WAVE,
        MIN_MUSIC_FRAME_THRESHOLD
    );
    // reset counter so first tick waits full interval
    musicFrameCounter = 0;
}

std::list<Enemy*> EnemyManager::getEnemies() {
    return enemies;
}

void EnemyManager::changeEnemyDirection() {
    movementDir = -movementDir;
    
    // move the enemies down
    for (EnemyBase* enemy : enemies) {
        Position p = enemy->getPosition();
        p.y -= ENEMY_DESCENT_AMOUNT;
        enemy->setPosition(p);
    }
}

void EnemyManager::playSFX() {
    AudioInfo* moveAudio = resourceMan->makeAudio(ENEMY_MOVE_SOUNDS[sfxPtr]);
    audioRenderer->playSound(*moveAudio);
    delete moveAudio;

    // Cycle the sound index from 0 to NUM_ENEMY_MOVE_SOUNDS - 1.
    sfxPtr = (sfxPtr + 1) % NUM_ENEMY_MOVE_SOUNDS;
}

bool EnemyManager::hitEdge() {
    for (Enemy* enemy : enemies) {
        int ex = enemy->getPosition().x;
        int er = ex + enemy->getImage()->getWidth();
        if ((ex <= 0 && movementDir < 0) || (er >= WINDOW_WIDTH && movementDir > 0)) {
            return true;
        }
    }
    return false;
}

void EnemyManager::setEnemySpeed(int speed) {
    enemySpeed = speed;
}

RedEnemy* EnemyManager::getRedEnemy() {
    return redEnemy;
}

void EnemyManager::updateAndRenderRedEnemy() {
    if(!redEnemy)
        return;
    
    if(redEnemy->getPosition().x > WINDOW_WIDTH) {
        visualRenderer->removeImage(redEnemy->getImage());
        delete redEnemy;
        redEnemy = nullptr;
        return;
    }
    
    redEnemy->update();
    redEnemy->render(visualRenderer);
}

void EnemyManager::clearAllEnemies() {
        // 1) kill & delete all live enemies
        for (Enemy* e : enemies) {
            visualRenderer->removeImage(e->getImage());
            delete e;
        }
        enemies.clear();
    
        // 2) delete any still‐exploding enemies
        for (EnemyBase* eb : dyingEnemies) {
            visualRenderer->removeImage(eb->getImage());
            delete eb;
        }
        dyingEnemies.clear();
    
        // 3) delete the red enemy if it exists
        if (redEnemy) {
            visualRenderer->removeImage(redEnemy->getImage());
            delete redEnemy;
            redEnemy = nullptr;
        }
}
