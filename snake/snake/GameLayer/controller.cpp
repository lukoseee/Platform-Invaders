#include "controller.hpp"

#include "constants.hpp"
#include <sstream>

Controller::Controller() {
    platformInterface = new PlatformInterface();
    renderer = new Renderer(platformInterface->getVisualRenderer());
    
    // init lib
    platformInterface->getVisualRenderer()->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SNAKE", false);
    platformInterface->getClockManager()->setTargetFrameRate(FPS);
    
    // set-up managers
    guiState = MAIN_MENU;
    leaderboardMan = new LeaderboardManager(platformInterface, renderer);
    gameMan = new GameManager(platformInterface, renderer);
    menuMan = new MainMenuManager(platformInterface, renderer);
}

Controller::~Controller() {
    delete leaderboardMan;
    delete gameMan;
    delete menuMan;
    delete renderer;
    delete platformInterface;
}

void Controller::loop() {
    while(true)
        switch(guiState) {
            case MAIN_MENU:
                menuMan->initalise();
                guiState = menuMan->loop();
                break;
            case GAME:
                gameMan->initalise();
                guiState = gameMan->loop();
                break;
            case LEADERBOARD:
                leaderboardMan->initalise();
                guiState = leaderboardMan->loop();
                break;
            case QUIT:
                return;
        }
}

