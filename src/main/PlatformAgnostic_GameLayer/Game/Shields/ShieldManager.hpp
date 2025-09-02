#pragma once

#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../GameManagerInterface.hpp"
#include "Shield.hpp"

#include <list>

enum class ShieldBlockType {
    UPPER_LEFT,
    UPPER_RIGHT,
    LOWER_LEFT,
    LOWER_RIGHT,
    SQUARE,
    EMPTY
};

/*
 Manager class to handle the maintence of any shields on the screen
 */
class ShieldManager : public GameManagerInterface{
public:
    ShieldManager(VisualRendererInterface*, ResourceManagerInterface*);
    ~ShieldManager();
    
    void updateAndRender() override;
    
    void initalise();
    void damageShield(Shield*);
    std::list<Shield*> getShields();
    
private:
    std::array<ImageInfo*, 4> loadShieldImages(ShieldBlockType type);
    void createShield(int startX, int startY);
    void removeShield(Shield*);
    
    std::list<Shield*> shields;
};


