#pragma once

#include "../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

class GameManagerInterface {
public:
    virtual void updateAndRender() = 0;
    
protected:
    VisualRendererInterface* visualRenderer;
    ResourceManagerInterface* resourceMan;
};
