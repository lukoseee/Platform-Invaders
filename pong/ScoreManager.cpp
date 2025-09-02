#include "scoreManager.hpp"

ScoreManager::ScoreManager(VisualRendererInterface* renderer, ResourceManagerInterface* resourceMan) {
    this->renderer = renderer;
    this->resourceMan = resourceMan;
    score = 0;
}

ScoreManager::~ScoreManager() {
    for (ImageInfo* img : headerText) {
        renderer->removeImage(img);
        delete img;
    }

    for (ImageInfo* img : digits) {
        renderer->removeImage(img);
        delete img;
    }

    delete header;
}

void ScoreManager::initalise(int x , int y) {

    ImageInfo* zero = convertDigit(0);
    renderer->renderImage(zero, x ,y);
    digits.push_back(zero);
    renderPosX = x;
    renderPosY = y;

}

void ScoreManager::incScore() {
    score++;
    renderScore();
}

int ScoreManager::getScore() {
    return score;
}

void ScoreManager::setScore(int i)
{
    score = i;
    renderScore();
}

void ScoreManager::renderScore() {
    // clear display
    for (ImageInfo* digit : digits) {
        renderer->removeImage(digit);
        delete digit;
    }
    digits.clear();

    // calculate display digits
    int n = score;
    while (n > 0) {
        int m = n % 10;
        digits.push_back(convertDigit(m));  // least significant digit first
        n /= 10;
    }

    int spacing = SCORE_SIZE;
    int i = 0;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        int x = renderPosX + i * spacing;
        renderer->renderImage(*it, x, renderPosY);
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

    if (path != "")
        return resourceMan->makeImage(path, SCORE_SIZE, SCORE_SIZE, true);

    return nullptr;
}
