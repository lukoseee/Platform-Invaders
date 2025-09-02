#pragma once

#include "../Snake/snake.hpp"
#include "../Apple/apple.hpp"
#include "../ScoreManager/scoreManager.hpp"

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../guiManagerInterface.hpp"

class GameManager : GUIManagerInterface{
public:
    GameManager(PlatformInterface*, Renderer*);
    ~GameManager();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;
    
private:
    void countdownLoop();
    std::string gameOverLoop();
    void processSnakeUI();
    bool outOfBounds(Position);
    
    Apple* apple;
    Snake* snake;
    ScoreManager* scoreManager;
    ImageInfo* background;
    std::list<ImageInfo*> countdown;
    std::list<ImageInfo*> chars;
    ImageInfo* gameOverHUD ;
};
