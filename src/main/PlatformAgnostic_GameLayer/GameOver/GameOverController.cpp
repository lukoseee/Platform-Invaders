#include "GameOverController.hpp"
#include "../Constants.hpp"

GameOverController::GameOverController(PlatformInterface* p) {
    resourceMan = p->getResourceManager();
    visualRenderer = p->getVisualRenderer();
    clockMan = p->getClockManager();
    audioRenderer = p->getAudioRenderer();
    userInputMan = p->getUserInputManager();
}

GameOverController::~GameOverController() {
    cleanUp();
}

void GameOverController::cleanUp() {
    visualRenderer->removeImage(background);
    delete background;
    background = nullptr;
    for(ImageInfo* img : chars) {
           visualRenderer->removeImage(img);
           delete img;
       }
       chars.clear();
       
       visualRenderer->removeImage(scoreDisplay);
       delete scoreDisplay;
    
    // Clean score digits
    for (ImageInfo* digit : scoreDigits) {
        visualRenderer->removeImage(digit);
        delete digit;
    }
    scoreDigits.clear();
}

void GameOverController::setScore(int score) {
    finalScore = score;
}

void GameOverController::initalise() {
    // Load Game Over background
    background = resourceMan->makeImage(GAME_OVER_IMAGE, WINDOW_WIDTH, WINDOW_HEIGHT, true);
    visualRenderer->renderImage(background, 0, 0);
    
    // Render numerical score
    renderScoreDigits();
    
    // Initialize name builder
    nameBuilder.clear();
    chars.clear();
}

void GameOverController::renderScoreDigits() {
    // Clear previous digits
    for(ImageInfo* digit : scoreDigits) {
        visualRenderer->removeImage(digit);
        delete digit;
    }
    scoreDigits.clear();

    // Convert score to individual digits
    std::string scoreStr = std::to_string(finalScore);
    int xPos = SCORE_VALUE_X;
    
    for(char c : scoreStr) {
        std::string path(1, c);  // "0" -> "0.png", "5" -> "5.png", etc.
        ImageInfo* digit = resourceMan->makeImage(path, 30, 30, true);
        visualRenderer->renderImage(digit, xPos, SCORE_VALUE_Y);
        scoreDigits.push_back(digit);
        xPos += DIGIT_SPACING;
    }
}

GUIState GameOverController::loop() {
    while (true) {
            while (!userInputMan->isEmpty()) {
                UserInput input = userInputMan->getNextInput();
                
                switch(input) {
                    case RETURN_DOWN:
                        if(!nameBuilder.empty()) {
                            // Write to scores.txt in "NAME,SCORE" format
                            resourceMan->writeFile("scores",
                                nameBuilder + "," + std::to_string(finalScore) + "\n", true);
                            cleanUp();
                            return MAIN_MENU;
                        }
                        break;
                        
                    case DELETE_DOWN:
                        if(!nameBuilder.empty()) {
                            nameBuilder.pop_back();
                            visualRenderer->removeImage(chars.back());
                            delete chars.back();
                            chars.pop_back();
                        }
                        break;
                        
                    // Handle letter inputs
                    case A_DOWN: addCharacter(A_PATH, 'A'); break;
                    case B_DOWN: addCharacter(B_PATH, 'B'); break;
                    case C_DOWN: addCharacter(C_PATH, 'C'); break;
                    case D_DOWN: addCharacter(D_PATH, 'D'); break;
                    case E_DOWN: addCharacter(E_PATH, 'E'); break;
                    case F_DOWN: addCharacter(F_PATH, 'F'); break;
                    case G_DOWN: addCharacter(G_PATH, 'G'); break;
                    case H_DOWN: addCharacter(H_PATH, 'H'); break;
                    case I_DOWN: addCharacter(I_PATH, 'I'); break;
                    case J_DOWN: addCharacter(J_PATH, 'J'); break;
                    case K_DOWN: addCharacter(K_PATH, 'K'); break;
                    case L_DOWN: addCharacter(L_PATH, 'L'); break;
                    case M_DOWN: addCharacter(M_PATH, 'M'); break;
                    case N_DOWN: addCharacter(N_PATH, 'N'); break;
                    case O_DOWN: addCharacter(O_PATH, 'O'); break;
                    case P_DOWN: addCharacter(P_PATH, 'P'); break;
                    case Q_DOWN: addCharacter(Q_PATH, 'Q'); break;
                    case R_DOWN: addCharacter(R_PATH, 'R'); break;
                    case S_DOWN: addCharacter(S_PATH, 'S'); break;
                    case T_DOWN: addCharacter(T_PATH, 'T'); break;
                    case U_DOWN: addCharacter(U_PATH, 'U'); break;
                    case V_DOWN: addCharacter(V_PATH, 'V'); break;
                    case W_DOWN: addCharacter(W_PATH, 'W'); break;
                    case X_DOWN: addCharacter(X_PATH, 'X'); break;
                    case Y_DOWN: addCharacter(Y_PATH, 'Y'); break;
                    case Z_DOWN: addCharacter(Z_PATH, 'Z'); break;
                    case ZERO_DOWN: addCharacter(ZERO_PATH, '0'); break;
                    case ONE_DOWN: addCharacter(ONE_PATH, '1'); break;
                    case TWO_DOWN: addCharacter(TWO_PATH, '2'); break;
                    case THREE_DOWN: addCharacter(THREE_PATH, '3'); break;
                    case FOUR_DOWN: addCharacter(FOUR_PATH, '4'); break;
                    case FIVE_DOWN: addCharacter(FIVE_PATH, '5'); break;
                    case SIX_DOWN: addCharacter(SIX_PATH, '6'); break;
                    case SEVEN_DOWN: addCharacter(SEVEN_PATH, '7'); break;
                    case EIGHT_DOWN: addCharacter(EIGHT_PATH, '8'); break;
                    case NINE_DOWN: addCharacter(NINE_PATH, '9'); break;
                    default: break;
                }
            }
            
            visualRenderer->updateDisplay();
            clockMan->synchronizeFrame();
        }
    }

void GameOverController::addCharacter(const char* path, char c) {
    if(nameBuilder.size() >= PLAYER_NAME_CHAR_LIMIT) return;
    
    nameBuilder += c;
    ImageInfo* charImage = resourceMan->makeImage(path, 30, 30, true);
    chars.push_back(charImage);
    
    int xPos = NAME_ENTRY_X + (PLAYER_NAME_CHAR_GAP * (chars.size()-1));
    visualRenderer->renderImage(charImage, xPos, NAME_ENTRY_Y);
}
