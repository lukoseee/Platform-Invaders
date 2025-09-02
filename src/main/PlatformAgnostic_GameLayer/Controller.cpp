#include "Controller.hpp"

Controller::Controller() {
    // init library
    platformInterface = new PlatformInterface();
    platformInterface->getVisualRenderer()->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders", false);
    platformInterface->getClockManager()->setTargetFrameRate(FPS);
    
    // init GUI controllers
    menuController = new MenuController(platformInterface);
    gameController = new GameController(platformInterface);
    gameOverController = new GameOverController(platformInterface);
    leaderboardController = new LeaderboardController(platformInterface);
    
    guiState = MAIN_MENU;
}

Controller::~Controller() {
}

void Controller::loop() {
    while(true)
        switch(guiState) {
            case MAIN_MENU:
                menuController->initalise();
                guiState = menuController->loop();
                break;
            case LEADERBOARD:
                leaderboardController->initalise();
                guiState = leaderboardController->loop();
                break;
            case GAME:
                gameController->initalise();
                guiState = gameController->loop();
                gameOverController->setScore(gameController->getScore());
                break;
            case GAME_OVER:
                gameOverController->initalise();
                guiState = gameOverController->loop();
                break;
            case QUIT:
                return;
        }
}

