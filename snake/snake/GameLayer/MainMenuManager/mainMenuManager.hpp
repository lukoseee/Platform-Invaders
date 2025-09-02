#pragma once

#include "../Snake/snake.hpp"

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../guiManagerInterface.hpp"

class MainMenuManager : GUIManagerInterface{
public:
    MainMenuManager(PlatformInterface*, Renderer*);
    ~MainMenuManager();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;

private:
    void renderUnderline(MenuOption);
    void playSelectSFX();
    
    Snake* snake;
    ImageInfo* menuScreen;
    ImageInfo* bar;
    
    
};
