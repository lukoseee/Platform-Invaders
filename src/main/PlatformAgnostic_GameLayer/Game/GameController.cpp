#include "GameController.hpp"
#include "Player/Player.hpp"
#include "Enemies/Enemy.hpp"
#include "Shields/Shield.hpp"
#include "Bullets/Bullet.hpp"
#include "Enemies/RedEnemy.hpp"
#include "../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../Constants.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../GUIInterface.hpp"
 
// Constructor initializes game state, HUD managers, and global respawn variables.
GameController::GameController(PlatformInterface* p)
{
    resourceMan = p->getResourceManager();
    visualRenderer = p->getVisualRenderer();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
    
    currentWave = INITIAL_WAVE_COUNT;
    waveRespawnFrameCounter = 0;
}

// Destructor cleans up resources.
GameController::~GameController()
{
    delete scoreManager;
    cleanUp();
}

// Cleans up resources and stops audio.
void GameController::cleanUp() {
    audioRenderer->stopAudio();
    
    delete scoreManager;
    scoreManager = nullptr; 
    
    delete livesManager;
    livesManager = nullptr;

    delete bulletManager;
    bulletManager = nullptr;

    delete enemyManager;
    enemyManager = nullptr;
    
    delete shieldManager;
    shieldManager = nullptr;
    
    visualRenderer->removeImage(player->getImage());
    delete player;
    player = nullptr;
}

// Initializes the game state, including HUD elements and player.
void GameController::initalise()
{
    // Initialize HUD elements.
    scoreManager = new ScoreManager(visualRenderer, resourceMan);
    scoreManager->initialise();
    
    livesManager = new LivesManager(visualRenderer, resourceMan);
    livesManager->initalise();
    
    enemyManager = new EnemyManager(visualRenderer, resourceMan, audioRenderer);
    enemyManager->spawnEnemies();
    
    bulletManager = new BulletManager(visualRenderer, resourceMan, audioRenderer);
    
    shieldManager = new ShieldManager(visualRenderer, resourceMan);
    shieldManager->initalise();

    // Create the initial player.
    player = new Player(resourceMan);

}

// Main game loop that handles input, updates game state, and renders graphics.
GUIState GameController::loop()
{
    while (true) {
        // handle input
        while (!userInputMan->isEmpty()) {
            processInput(userInputMan->getNextInput());
        }
        
        player->update();
        player->render(visualRenderer);
        
        shieldManager->updateAndRender();
        bulletManager->updateAndRender();
        enemyManager->updateAndRender();
        scoreManager->updateAndRender();
        livesManager->updateAndRender();
        
        // clamp player to screen
        Position p = player->getPosition();
        int pw = player->getImage()->getWidth();
        p.x = std::max(0, std::min(p.x, WINDOW_WIDTH - pw));
        player->setPosition(p);
        
        // enemy shooting
        std::list<Enemy*> enemies = enemyManager->getEnemies();
        for(Enemy* enemy : enemies) {
            if (enemy->getShootCooldown() == 0) {
                bulletManager->fireEnemyBullet(enemy);
                enemy->resetShootCooldown();
            }
        }
        
        if(player->isShooting() && player->getShootCooldown() < 0 && !player->isHoldShootDown()) {
            bulletManager->firePlayerBullet(player);
            player->resetShootCooldown();
            player->setHoldShootDown(true);
        }
        
        // check game over by enemy reach or all destroyed
        int minY = WINDOW_HEIGHT;
        for(Enemy* enemy : enemies) {
            minY = std::min(minY, enemy->getPosition().y);
        }
        
        // break from game loop
        if (minY <= GAME_OVER_ENEMY_Y_THRESHOLD || livesManager->getLives() == 0) {
            break;
        }
        
        if (!enemyManager->enemiesLeft()) {
            processWaveCompletion();
        }
    
        for(Shield* shield : shieldManager->getShields()) {
            if(bulletManager->checkCollisions(shield))
                shieldManager->damageShield(shield);
        }
        
        if(bulletManager->checkCollisions(player)) {
            // play SFX
            AudioInfo* deathAudio = resourceMan->makeAudio(PLAYER_DEATH_SOUND);
            audioRenderer->playSound(*deathAudio);
            delete deathAudio;
            
            processPlayerDeath();
        }
        
        RedEnemy* redEnemy = enemyManager->getRedEnemy();
        if(redEnemy && bulletManager->checkCollisions(redEnemy)) {
            // play SFX
            AudioInfo* explosionAudio = resourceMan->makeAudio(ENEMY_EXPLOSION_SOUND);
            audioRenderer->playSound(*explosionAudio);
            delete explosionAudio;
            
            // update score
            int randomIndex = rand() % RED_ENEMY_SCORE_VALUES_SIZE;
            scoreManager->addScore(RED_ENEMY_SCORE_VALUES[randomIndex]);
            enemyManager->killEnemy(redEnemy);
        }
        
        for(Enemy* enemy : enemies) {
            if(!enemy->isDying() > 0 && bulletManager->checkCollisions(enemy)) {
                // play SFX
                AudioInfo* explosionAudio = resourceMan->makeAudio(ENEMY_EXPLOSION_SOUND);
                audioRenderer->playSound(*explosionAudio);
                delete explosionAudio;
                
                // update score
                scoreManager->addScore(NORMAL_ENEMY_SCORE);
                enemyManager->killEnemy(enemy);
            }
        }
        
    
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
    }
    
    // BEFORE CLEANUP: Capture final score
    finalScore = scoreManager->getScore();
    cleanUp();
    return GAME_OVER;
}

int GameController::getScore() const {
    return finalScore; // Return stored value, not live scoreManager
}

void GameController::processWaveCompletion() {
    audioRenderer->stopAudio();
    currentWave++;
    bulletManager->removeAllBullets();
    enemyManager->clearAllEnemies();
    
    int waveRespawnFrameCounter = 0;
    
    while(true) {
        
        // Block & discard input during delay
        while (!userInputMan->isEmpty()) {
            userInputMan->getNextInput();
        }
        
        if (waveRespawnFrameCounter >= 120) {
            enemyManager->spawnEnemies();
            
            // Increase speed for new waves (modified line)
            enemyManager->setEnemySpeed(ENEMY_GROUP_SPEED + (currentWave - 1) * ENEMY_SPEED_INCREMENT_PER_WAVE);
            break;
        }
        
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
        waveRespawnFrameCounter++;
    }
    
    player->setPosition({PLAYER_START_X, PLAYER_START_Y});
}

// Updated processInput() to accept a UserInput enum.
void GameController::processInput(UserInput input) {
    switch(input) {
        case A_DOWN: player->setMovementDirection(LEFT); break;
        case D_DOWN: player->setMovementDirection(RIGHT); break;
        case S_DOWN: player->setShooting(true); break;
        case S_UP: 
            player->setShooting(false);     
            player->setHoldShootDown(false);
            break;
        default: player->setMovementDirection(STATIONARY); break;
    }
}

// Resets the player position to the starting point.
void GameController::processPlayerDeath() {
    player->kill();
    livesManager->decrementLives();
    
    // Play death sound.
    AudioInfo* deathAudio = resourceMan->makeAudio(PLAYER_DEATH_SOUND);
    audioRenderer->playSound(*deathAudio);
    delete deathAudio;
    
    int frameCount = 0;
    while(true) {
        if(frameCount > PLAYER_DEATH_DURATION) {
            break;
        }
        
        // discard user inputs
        while (!userInputMan->isEmpty()) {
            userInputMan->getNextInput();
        }
    
        player->update();
        player->render(visualRenderer);

        clockMan->synchronizeFrame();
        visualRenderer->updateDisplay();
        frameCount++;
    }
    
    bulletManager->removeAllBullets();
    
    visualRenderer->removeImage(player->getImage());
    delete player;
    
    // Create the initial player.
    player = new Player(resourceMan);
}

