#pragma once

#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../GameManagerInterface.hpp"
#include "Enemy.hpp"
#include "RedEnemy.hpp"
#include "EnemyBase.hpp"

#include <list>

/*
 Class which handles the maintaing of all enemies for the game layer
 */
class EnemyManager : public GameManagerInterface{
public:
    EnemyManager(VisualRendererInterface*, ResourceManagerInterface*, AudioRendererInterface*);
    ~EnemyManager();
    
    // update and render all enemies
    void updateAndRender() override;
    
    bool enemiesLeft();
    void spawnEnemies();
    void setEnemySpeed(int);
    RedEnemy* getRedEnemy();
    void killEnemy(EnemyBase*);
    std::list<Enemy*> getEnemies();

    void clearAllEnemies();
    
private:
    void spawnRedEnemy();
    void changeEnemyDirection();
    void playSFX();
    bool hitEdge();
    void removeEnemy(EnemyBase*);
    void updateAndRenderRedEnemy();
    
    AudioRendererInterface* audioRenderer;
    
    RedEnemy* redEnemy;
    std::list<Enemy*> enemies;
    std::list<EnemyBase*> dyingEnemies;
    
    int frameCount;
    int sfxPtr;
    int movementDir;
    int enemySpeed;

    int musicFrameCounter;    
    int musicFrameThreshold; 
};
