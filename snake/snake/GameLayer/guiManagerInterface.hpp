#pragma once

#include "Util/util.hpp"
#include "../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class GUIManagerInterface {
public:
    virtual void initalise() = 0;
    virtual GUIState loop() = 0;
    virtual void cleanUp() = 0;
    
protected:
    ResourceManagerInterface* resourceMan;
    VisualRendererInterface* visualRenderer;
    ClockManagerInterface* clockMan;
    AudioRendererInterface* audioRenderer;
    UserInputManagerInterface* userInputMan;
    
    Renderer* renderer;
};
