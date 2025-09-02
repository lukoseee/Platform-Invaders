#pragma once

#include <list>

#include "constants.hpp"
#include "Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class ScoreManager {
public:
    ScoreManager(VisualRendererInterface*, ResourceManagerInterface*);
    ~ScoreManager();
    void initalise(int x , int y);
    void incScore();
    int getScore();
    void setScore(int i);

private:
    ImageInfo* convertDigit(int);
    void renderScore();

    VisualRendererInterface* renderer;
    ResourceManagerInterface* resourceMan;
    int renderPosX;
    int renderPosY;
    int score;
    std::list<ImageInfo*> digits;
    std::list<ImageInfo*> headerText;
    ImageInfo* header;
};
