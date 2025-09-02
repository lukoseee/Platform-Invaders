#pragma once

#include "../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "GUIState.hpp"
#include "Menu/MenuController.hpp"
#include "Game/GameController.hpp"
#include "GameOver/GameOverController.hpp"
#include "Leaderboard/LeaderboardController.hpp"

/*
 Basic controller class managing the transitions between GUIs
 */
class Controller {
public:
    Controller();
    ~Controller();
    
    void loop();
    
private:
    PlatformInterface* platformInterface;
    
    GUIState guiState;
    MenuController* menuController;
    GameController* gameController;
    GameOverController* gameOverController;
    LeaderboardController* leaderboardController;
};
