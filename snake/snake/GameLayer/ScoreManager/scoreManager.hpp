#pragma once

#include <list>

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class ScoreManager {
public:
    ScoreManager(Renderer*, ResourceManagerInterface*);
    ~ScoreManager();
    void initalise();
    void incScore();
    int getScore();
    
private:
    ImageInfo* convertDigit(int);
    void renderScore();
    
    Renderer* renderer;
    ResourceManagerInterface* resourceMan;
    int score;
    std::list<ImageInfo*> digits;
    std::list<ImageInfo*> headerText;
    ImageInfo* header;
};
