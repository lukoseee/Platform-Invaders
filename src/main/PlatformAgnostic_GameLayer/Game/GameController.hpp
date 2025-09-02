#pragma once

#include <list>
#include <string>
#include "Entity.hpp"
#include "../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "Score/ScoreManager.hpp"
#include "Lives/LivesManager.hpp"
#include "Enemies/EnemyManager.hpp"
#include "Bullets/BulletManager.hpp"
#include "Shields/ShieldManager.hpp"
#include "Player/Player.hpp"
#include "../GUIInterface.hpp"

// Possible game states.
enum class GameState {
    INTRO,
    RUNNING,
    GAME_OVER,
    WAVE_COMPLETE
};

class GameController : public GUIInterface{
public:
    GameController(PlatformInterface*);
    ~GameController();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;
    int getScore() const;

private:
    void processInput(UserInput input);

    // Game over handling.
    void removeIntroBackground();
    void handleGameOver();
    void resetGame();
    void processWaveCompletion();
    void processPlayerDeath();
    int finalScore;

    ScoreManager* scoreManager;  // Displays the score.
    LivesManager* livesManager;  // Displays the player's remaining lives.
    EnemyManager* enemyManager;
    BulletManager* bulletManager;
    ShieldManager* shieldManager;
    Player* player;


    // Wave mechanism management
    int currentWave;
    int waveRespawnFrameCounter;
    void resetPlayerPosition();
    void clearEnemiesAndBullets();
    
};
