#pragma once

#include "EnemyBase.hpp"

class RedEnemy : public EnemyBase{
public:
    RedEnemy(ResourceManagerInterface* resourceMan);
    virtual ~RedEnemy() override;

    void update() override;
};
