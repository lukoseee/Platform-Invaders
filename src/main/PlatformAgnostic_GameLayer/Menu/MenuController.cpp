#include "MenuController.hpp"
#include "../Constants.hpp"

MenuController::MenuController(PlatformInterface* p) {
    resourceMan = p->getResourceManager();
    visualRenderer = p->getVisualRenderer();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
}

MenuController::~MenuController() {
    cleanUp();
}

void MenuController::cleanUp() {
    visualRenderer->removeImage(background);
    delete background;
    background = nullptr;
    
    visualRenderer->removeImage(arrow);
    delete arrow;
    arrow = nullptr;
}

void MenuController::initalise() {
    // render background
    background = resourceMan->makeImage(INTRO_BACKGROUND_IMAGE, WINDOW_WIDTH, WINDOW_HEIGHT, true);
    visualRenderer->renderImage(background, 0, 0);
    
    // initalise arrow data
    arrowPositions = {
        START_GAME_Y,
        LEADERBOARD_Y,
        QUIT_Y
    };
    arrowPositionPtr = 0;
    
    // render arrow
    arrow = resourceMan->makeImage(ARROW_IMAGE, ARROW_W, ARROW_H, true);
    renderArrow();
}

GUIState MenuController::loop() {
    while(true) {
        bool enterFlag = false;
        
        // handle user input
        while (!userInputMan->isEmpty()) {
            switch(userInputMan->getNextInput()) {
                  
                // change arrow pos ptr in response to up/down arrows
                case UP_ARROW_DOWN:
                    if(arrowPositionPtr < arrowPositions.size() - 1) {
                        arrowPositionPtr++;
                        renderArrow();
                    }
                    break;
                    
                case DOWN_ARROW_DOWN:
                    if(arrowPositionPtr > 0) {
                        arrowPositionPtr--;
                        renderArrow();
                    }
                    break;
                    
                case RETURN_DOWN: enterFlag = true; break;
                default: break;
            }
        }
        
        // check if user has slected an option
        if(enterFlag) {
            cleanUp();
            switch(arrowPositionPtr) {
                case 0: return QUIT;
                case 1: return GAME;
                case 2: return LEADERBOARD;
                default:
                    std::cerr << "ERR: MenuController.arrowPositionPtr invalid value" << std::endl;
                    exit(EXIT_FAILURE);
            }
        }
        
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
    }
}

void MenuController::renderArrow() {
    visualRenderer->removeImage(arrow);
    visualRenderer->renderImage(arrow, ARROW_X, arrowPositions[arrowPositionPtr]);
}
