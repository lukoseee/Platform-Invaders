#pragma once

#include "GUIState.hpp"
#include "../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class GUIInterface {
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
};
