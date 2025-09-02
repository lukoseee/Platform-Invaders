#include "scoreManager.hpp"

ScoreManager::ScoreManager(Renderer* renderer, ResourceManagerInterface* resourceMan) {
    this->renderer = renderer;
    this->resourceMan = resourceMan;
    score = 0;
}

ScoreManager::~ScoreManager() {
    for (ImageInfo* img : headerText) {
        renderer->remove(img);
        delete img;
    }

    for (ImageInfo* img : digits) {
        renderer->remove(img);
        delete img;
    }
    
    delete header;
}

void ScoreManager::initalise() {
    // set-up header
    header = resourceMan->makeImage(SCORE_HEADER_PATH, CELL_SIZE * NUM_CELLS, CELL_SIZE * 2, true);
    renderer->render(header, {0, 20});
    
    // display "SCORE" text
    headerText.push_front(resourceMan->makeImage(S_PATH, CELL_SIZE, CELL_SIZE, true));
    headerText.push_front(resourceMan->makeImage(C_PATH, CELL_SIZE, CELL_SIZE, true));
    headerText.push_front(resourceMan->makeImage(O_PATH, CELL_SIZE, CELL_SIZE, true));
    headerText.push_front(resourceMan->makeImage(R_PATH, CELL_SIZE, CELL_SIZE, true));
    headerText.push_front(resourceMan->makeImage(E_PATH, CELL_SIZE, CELL_SIZE, true));
    headerText.push_front(resourceMan->makeImage(COLON_PATH, CELL_SIZE, CELL_SIZE, true));
    
    int i = 0;
    for(ImageInfo* img : headerText) {
        renderer->render(img, {GAME_SCORE_POS.x - 3 - i, GAME_SCORE_POS.y});
        i++;
    }
    
    renderScore();
}

void ScoreManager::incScore(){
    score++;
    renderScore();
}

int ScoreManager::getScore() {
    return score;
}

void ScoreManager::renderScore() {
    // clear display
    for(ImageInfo* digit : digits) {
        renderer->remove(digit);
        delete digit;
    }
    digits.clear();
    
    // calculate display digits
    if(score == 0)
        digits.push_back(convertDigit(0));
    else {
        int n = score;
        while (n > 0) {
            int m = n % 10;
            digits.push_back(convertDigit(m));
            n /= 10;
        }
    }
    
    // display score
    int i = 0;
    for(ImageInfo* digit : digits) {
        renderer->render(digit, {GAME_SCORE_POS.x - i, GAME_SCORE_POS.y});
        i++;
    }
}

// convert an int digit to an ImageInfo of that digit
ImageInfo* ScoreManager::convertDigit(int n) {
    std::string path = "";
    
    switch (n) {
        case 0: path = ZERO_PATH; break;
        case 1: path = ONE_PATH; break;
        case 2: path = TWO_PATH; break;
        case 3: path = THREE_PATH; break;
        case 4: path = FOUR_PATH; break;
        case 5: path = FIVE_PATH; break;
        case 6: path = SIX_PATH; break;
        case 7: path = SEVEN_PATH; break;
        case 8: path = EIGHT_PATH; break;
        case 9: path = NINE_PATH; break;
        default: break;
    }
    
    if(path != "")
        return resourceMan->makeImage(path, CELL_SIZE, CELL_SIZE, true);
    
    return nullptr;
}
