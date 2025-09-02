#include "gameManager.hpp"

GameManager::GameManager(PlatformInterface* p, Renderer* renderer) {
    this->renderer = renderer;
    
    visualRenderer = p->getVisualRenderer();
    resourceMan = p->getResourceManager();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
}

GameManager::~GameManager() {
    cleanUp();
}

void GameManager::cleanUp() {
    renderer->remove(background);
    delete background;
    background = nullptr;
    
    delete snake;
    snake = nullptr;
    
    delete apple;
    apple = nullptr;
    
    delete scoreManager;
    scoreManager = nullptr;
    
    for(ImageInfo* elem : countdown) {
        renderer->remove(elem);
        delete elem;
    }
    countdown.clear();
    
    for(ImageInfo* elem : chars) {
        renderer->remove(elem);
        delete elem;
    }
    chars.clear();
    
    renderer->remove(gameOverHUD);
    delete gameOverHUD;
    gameOverHUD = nullptr;
}

void GameManager::initalise() {
    // render background
    background = resourceMan->makeImage(BACKGROUND_PATH, NUM_CELLS * CELL_SIZE, NUM_CELLS * CELL_SIZE, true);
    renderer->render(background, {0, 0});
    
    // instantiate game entities
    snake = new Snake(renderer, resourceMan, INITAL_SNAKE_LENGTH, RIGHT);
    snake->initalise(GAME_INITAL_SNAKE_POS);
    apple = new Apple(renderer, resourceMan->makeImage(APPLE_PATH, CELL_SIZE, CELL_SIZE, true), snake);
    apple->spawn();
    
    // set-up score manager
    scoreManager = new ScoreManager(renderer, resourceMan);
    scoreManager->initalise();
}

GUIState GameManager::loop() {
    // start countdown
    countdownLoop();
    
    int frameCount = 0;
    
    // game loop
    while(true) {
        if(snake->getState() == DEAD) {
            break;
        }
        
        processSnakeUI();
        
        // replay music whenever it ends
        if(frameCount % GAME_MUSIC_FRAME_THRES == 0) {
            AudioInfo* music = resourceMan->makeAudio(GAME_MUSIC);
            audioRenderer->playSound(*music);
            delete music;
        }
        
        if(frameCount % FRAME_THRES == 0)
            snake->update();
        
        // when the snake 'hits' the apple
        if(snake->colliding(apple->getPos())) {
            apple->spawn();
            snake->incLength();
            scoreManager->incScore();
            
            AudioInfo* sfx = resourceMan->makeAudio(APPLE_COLLECT_SFX);
            audioRenderer->playSound(*sfx);
            delete sfx;
        }
        
        // handle snake death logic
        if(snake->getState() != DEAD && (snake->selfColliding() || outOfBounds(snake->getHeadPos()))) {
            snake->setState(DYING);
            snake->update();
            
            audioRenderer->stopAudio();
            AudioInfo* sfx = resourceMan->makeAudio(DEATH_SFX);
            audioRenderer->playSound(*sfx);
            delete sfx;
        }
        
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
        frameCount++;
    }
        
    // hanlde game over and store name
    std::string name = gameOverLoop();

    // write to file
    resourceMan->writeFile(SCORES_TXT, name + ',' + std::to_string(scoreManager->getScore()) + '\n', true);
    
    cleanUp();
    return MAIN_MENU;
}

void GameManager::countdownLoop() {
    int frameCount = 0;
    
    // countdown assets
    countdown.push_back(resourceMan->makeImage(THREE_PATH, CELL_SIZE, CELL_SIZE, true));
    countdown.push_back(resourceMan->makeImage(TWO_PATH, CELL_SIZE, CELL_SIZE, true));
    countdown.push_back(resourceMan->makeImage(ONE_PATH, CELL_SIZE, CELL_SIZE, true));
    renderer->render(countdown.front(), GAME_COUNTDOWN_POS);
    
    // countdown loop
    while(true) {
        if(frameCount % FPS == 0) {
            renderer->remove(countdown.front());
            delete countdown.front();
            countdown.pop_front();
            
            if(countdown.empty())
                break;
            
            renderer->render(countdown.front(), GAME_COUNTDOWN_POS);
        }
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
        frameCount++;
    }
}

std::string GameManager::gameOverLoop() {
    // render HUD
    gameOverHUD = resourceMan->makeImage(GAME_OVER_HUD, GAME_OVER_HUD_WIDTH, GAME_OVER_HUD_HEIGHT, true);
    renderer->render(gameOverHUD, GAME_OVER_HUD_POS);
    
    std::string nameBuilder = "";
    
    // game over loop
    while(true) {
        Position pos = {PLAYER_NAME_OFFSET.x + (PLAYER_NAME_CHAR_GAP * nameBuilder.size()), PLAYER_NAME_OFFSET.y};
        
        bool success = false;
        bool enterFlag = false;
        std::string path = "";
        
        // Allow the user to enter their name
        while(!userInputMan->isEmpty()) {
            success = true;
            UserInput input = userInputMan->getNextInput();
            switch (input) {
                case A_DOWN: path = A_PATH; nameBuilder += 'A'; break;
                case B_DOWN: path = B_PATH; nameBuilder += 'B'; break;
                case C_DOWN: path = C_PATH; nameBuilder += 'C'; break;
                case D_DOWN: path = D_PATH; nameBuilder += 'D'; break;
                case E_DOWN: path = E_PATH; nameBuilder += 'E'; break;
                case F_DOWN: path = F_PATH; nameBuilder += 'F'; break;
                case G_DOWN: path = G_PATH; nameBuilder += 'G'; break;
                case H_DOWN: path = H_PATH; nameBuilder += 'H'; break;
                case I_DOWN: path = I_PATH; nameBuilder += 'I'; break;
                case J_DOWN: path = J_PATH; nameBuilder += 'J'; break;
                case K_DOWN: path = K_PATH; nameBuilder += 'K'; break;
                case L_DOWN: path = L_PATH; nameBuilder += 'L'; break;
                case M_DOWN: path = M_PATH; nameBuilder += 'M'; break;
                case N_DOWN: path = N_PATH; nameBuilder += 'N'; break;
                case O_DOWN: path = O_PATH; nameBuilder += 'O'; break;
                case P_DOWN: path = P_PATH; nameBuilder += 'P'; break;
                case Q_DOWN: path = Q_PATH; nameBuilder += 'Q'; break;
                case R_DOWN: path = R_PATH; nameBuilder += 'R'; break;
                case S_DOWN: path = S_PATH; nameBuilder += 'S'; break;
                case T_DOWN: path = T_PATH; nameBuilder += 'T'; break;
                case U_DOWN: path = U_PATH; nameBuilder += 'U'; break;
                case V_DOWN: path = V_PATH; nameBuilder += 'V'; break;
                case W_DOWN: path = W_PATH; nameBuilder += 'W'; break;
                case X_DOWN: path = X_PATH; nameBuilder += 'X'; break;
                case Y_DOWN: path = Y_PATH; nameBuilder += 'Y'; break;
                case Z_DOWN: path = Z_PATH; nameBuilder += 'Z'; break;
                case RETURN_DOWN:
                    success = false;
                    enterFlag = true;
                    break;
                case DELETE_DOWN:
                    success = false;
                    if(nameBuilder.size() > 0) {
                        nameBuilder.pop_back();
                        
                        // derender back char
                        renderer->remove(chars.back());
                        delete chars.back();
                        chars.pop_back();
                    }
                    break;
                default: success = false; break;
            }
            
            // render any characters pressed
            if(success && nameBuilder.size() <= PLAYER_NAME_CHAR_LIMIT) {
                ImageInfo* img = resourceMan->makeImage(path, CELL_SIZE, CELL_SIZE, true);
                chars.push_back(img);
                renderer->render(img, pos);
            }
        }
        
        if(enterFlag && nameBuilder.size() > 0)
            break;
        
        visualRenderer->updateDisplay();
        clockMan->synchronizeFrame();
    }
    return nameBuilder;
}

void GameManager::processSnakeUI() {
    while(!userInputMan->isEmpty()) {
        UserInput input = userInputMan->getNextInput();
        switch(input) {
            case W_DOWN:
                snake->changeDirection(UP);
                break;
            case A_DOWN:
                snake->changeDirection(LEFT);
                break;
            case S_DOWN:
                snake->changeDirection(DOWN);
                break;
            case D_DOWN:
                snake->changeDirection(RIGHT);
                break;
            default:
                break;
        }
    }
}

bool GameManager::outOfBounds(Position pos) {
    return (pos.x < 0 || pos.x >= NUM_CELLS || pos.y < 0 || pos.y >= NUM_CELLS);
}
