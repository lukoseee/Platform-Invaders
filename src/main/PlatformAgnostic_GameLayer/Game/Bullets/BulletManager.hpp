#pragma once

#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../GameManagerInterface.hpp"
#include "Bullet.hpp"
#include "../Player/Player.hpp"
#include "../Shields/Shield.hpp"
#include "../Enemies/Enemy.hpp"
#include "../Enemies/EnemyBase.hpp"
#include "../Entity.hpp"

#include <list>

/*
 Class which handles anu bullet management for the game layer.
 
 Collision checking with bullets can be done via this manager
 */
class BulletManager : public GameManagerInterface{
public:
    BulletManager(VisualRendererInterface*, ResourceManagerInterface*, AudioRendererInterface*);
    ~BulletManager();
    
    // update and render all bullets
    void updateAndRender() override;
    
    // overload exposed collision check allows Game Controller to disregard
    // bullet ownership and checks collisions only with the valid set of bullets
    // e.g. collions for a player only need to be checked against enemy bullets
    bool checkCollisions(Player* player);
    bool checkCollisions(Shield* shield);
    bool checkCollisions(EnemyBase* enemy);
    
    void fireEnemyBullet(Enemy* enemy);
    void firePlayerBullet(Player* player);
    void removeAllBullets();
    
private:
    bool colliding(Entity*, std::list<Bullet*>*);
    void removeBullet(Bullet*, std::list<Bullet*>*);
    bool outOfBounds(Bullet*);
    void updateBulletList(std::list<Bullet*>*);
    
    AudioRendererInterface* audioRenderer;
    
    // lists maintaining ownership of the bullets for collision checking optamisation
    std::list<Bullet*> playerBullets;
    std::list<Bullet*> enemyBullets;
};
