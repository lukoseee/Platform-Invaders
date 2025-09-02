#pragma once

#include "Renderer/renderer.hpp"
#include "GameManager/gameManager.hpp"
#include "LeaderboardManager/leaderboardManager.hpp"
#include "MainMenuManager/mainMenuManager.hpp"
#include "../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class Controller {
public:
    Controller();
    ~Controller();
    
    void loop();
    
private:
    LeaderboardManager* leaderboardMan;
    GameManager* gameMan;
    MainMenuManager* menuMan;
    PlatformInterface* platformInterface;
    Renderer* renderer;
    
    GUIState guiState;
};
