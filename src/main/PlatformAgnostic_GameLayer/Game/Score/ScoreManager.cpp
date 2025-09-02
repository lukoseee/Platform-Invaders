#include "ScoreManager.hpp"
#include <string>
#include "../../Constants.hpp"

ScoreManager::ScoreManager(VisualRendererInterface* visualRenderer, ResourceManagerInterface* resourceMan)
{
    this->visualRenderer = visualRenderer;
    this->resourceMan = resourceMan;
    score = 0;
    lastRenderedScore = -1;
}

ScoreManager::~ScoreManager() {
    for (ImageInfo* digit : digits) {
        visualRenderer->removeImage(digit);
        delete digit;
    }
    digits.clear();
    
    visualRenderer->removeImage(headerImage);
    delete headerImage;
    headerImage = nullptr;
}

void ScoreManager::updateAndRender() {
    if(lastRenderedScore == score)
        return;
    
    // clear display
    for(ImageInfo* digit : digits) {
        visualRenderer->removeImage(digit);
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
        visualRenderer->renderImage(digit, backgroundX + 100 +headerImage->getWidth() - (i * digit->getWidth()), backgroundY);
        i++;
    }
    
    lastRenderedScore = score;
}

void ScoreManager::initialise() {
    headerImage = resourceMan->makeImage(SCORE_IMAGE, 100, 20, true);
    visualRenderer->renderImage(headerImage, backgroundX, backgroundY);

    updateAndRender();
}

void ScoreManager::addScore(int value) {
    score += value;
}

void ScoreManager::resetScore() {
    score = 0;
}

int ScoreManager::getScore() const {
    return score;
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
        return resourceMan->makeImage(path, 20, 20, true);
    
    return nullptr;
}
