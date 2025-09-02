#include "mainMenuManager.hpp"

MainMenuManager::MainMenuManager(PlatformInterface* p, Renderer* renderer) {
    this->renderer = renderer;
    resourceMan = p->getResourceManager();
    visualRenderer = p->getVisualRenderer();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
}

MainMenuManager::~MainMenuManager() {
    cleanUp();
}

void MainMenuManager::cleanUp() {
    
    renderer->remove(menuScreen);
    delete menuScreen;
    menuScreen = nullptr;
    
    delete snake;
    snake = nullptr;
    
    renderer->remove(bar);
    delete bar;
    bar = nullptr;

}

void MainMenuManager::initalise() {
    // set-up background
    menuScreen = resourceMan->makeImage(MENU_SCREEN, WINDOW_WIDTH, WINDOW_HEIGHT, true);
    renderer->render(menuScreen, {0,0});
    
    // set-up snake
    snake = new Snake(renderer, resourceMan, INITAL_SNAKE_LENGTH, UP);
    snake->initalise(MENU_INITAL_SNAKE_POS);
}

GUIState MainMenuManager::loop() {
    // configure variables for identifying which menu option is selected
    std::vector<MenuOption> menuOptions = {START, SCORES, MENU_QUIT};
    int selected = 0;
    int enterFlag = false;
    
    // configure the underline bar for the selected menu option
    renderUnderline(menuOptions[selected]);
    
    int frameCount = 0;
    
    // below is list of directions which will be processed by the snake
    // it forms a complete cycle and looks to emulate some 'randomness'
    // the snake acts as a visual engagement for the user when viewing the
    // main menu.
    
    // duplicate directions (e.g. RIGHT, RIGHT) will do nothing but are
    // included for clarity and prevents the need to track how long
    // the snake travels in each direction
    int dirPtr = 0;
    std::vector<Direction> directions = {
        RIGHT, RIGHT, RIGHT, RIGHT, UP, RIGHT,
        RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
        RIGHT, UP, UP, RIGHT, RIGHT, UP,
        UP, UP, UP, UP, UP, UP,
        LEFT, LEFT, UP, UP, LEFT, UP,
        UP, LEFT, LEFT, LEFT, LEFT, LEFT,
        LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,
        LEFT, LEFT, UP, RIGHT, RIGHT, RIGHT,
        RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
        RIGHT, RIGHT, RIGHT, DOWN, DOWN, RIGHT,
        DOWN, RIGHT, DOWN, DOWN, DOWN, DOWN,
        DOWN, LEFT, DOWN, DOWN, LEFT, LEFT,
        DOWN, DOWN, DOWN, DOWN, LEFT, LEFT,
        LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,
        LEFT, LEFT, LEFT, LEFT, DOWN, RIGHT,
        RIGHT, RIGHT,
    };
    
    // UI loop
    while(true) {
        // handle user input
        while(!userInputMan->isEmpty()) {
            UserInput input = userInputMan->getNextInput();
            
            // up/down arrow keys to select different menu options
            switch(input) {
                case UP_ARROW_DOWN:
                    if(selected > 0) {
                        selected--;
                        renderer->remove(bar);
                        delete bar;
                        renderUnderline(menuOptions[selected]);
                        playSelectSFX();
                    }
                    break;
                case DOWN_ARROW_DOWN:
                    if(selected < menuOptions.size() - 1) {
                        selected++;
                        renderer->remove(bar);
                        delete bar;
                        renderUnderline(menuOptions[selected]);
                        playSelectSFX();

                    }
                    break;
                case RETURN_DOWN: enterFlag = true; break;
                default: break;
            }
        }
        
        // once ENTER is pressed, process the selected menu option
        if(enterFlag) {
            cleanUp();
            // stop anything playing
            audioRenderer->stopAudio();
            
            // play start game SFX
            AudioInfo* sfx = resourceMan->makeAudio(START_SFX);
            audioRenderer->playSound(*sfx);
            delete sfx;
            
            switch(menuOptions[selected]) {
                case START: return GAME;
                case SCORES: return LEADERBOARD;
                case MENU_QUIT: return QUIT;
            }
        }
        
        // update snake
        if(frameCount % FRAME_THRES == 0) {
            snake->changeDirection(directions[dirPtr++ % directions.size()]);
            snake->update();
        }
        
        if(frameCount % MENU_MUSIC_FRAME_THRES == 0) {
            AudioInfo* music = resourceMan->makeAudio(MENU_MUSIC);
            audioRenderer->playSound(*music);
            delete music;
        }
        
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
        frameCount++;
    }
}

// helper function to handle the underlining of selected menu options
void MainMenuManager::renderUnderline(MenuOption option) {
    std::string path;
    int width;
    Position pos;
    
    switch(option) {
        case START:
            path = START_UNDERLINE_BAR;
            width = START_BAR_WIDTH;
            pos = START_BAR_POS;
            break;
        case SCORES:
            path = SCORES_UNDERLINE_BAR;
            width = SCORES_BAR_WIDTH;
            pos = SCORES_BAR_POS;
            break;
        case MENU_QUIT:
            path = QUIT_UNDERLINE_BAR;
            width = QUIT_BAR_WIDTH;
            pos = QUIT_BAR_POS;
            break;
    }
    bar = resourceMan->makeImage(path, width * CELL_SIZE, CELL_SIZE / 2, true);
    renderer->render(bar, pos);
}

void MainMenuManager::playSelectSFX() {
    AudioInfo* sfx = resourceMan->makeAudio(SELECT_SFX);
    audioRenderer->playSound(*sfx);
    delete sfx;
}
