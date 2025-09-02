#pragma once

#include "../OtherInterfaces/AudioRendererInterface.hpp"
#include "../OtherInterfaces/VisualRendererInterface.hpp"
#include "../OtherInterfaces/UserInputManagerInterface.hpp"
#include "../OtherInterfaces/ResourceManagerInterface.hpp"
#include "../OtherInterfaces/ClockManagerInterface.hpp"


/*
 The PlatformInterface functions as the centerpoint for the
 platform-abstraction provided by the library.
 
 Various delegate managers are provided to the game layer. These can be
 accessed via the PlatformInterface. Relevent OS-specific implementations
 of each delegate is conditionally constructed based upon the running OS.
 */
class PlatformInterface {
public:
    PlatformInterface(void);
    
    AudioRendererInterface* getAudioRenderer(void);
    VisualRendererInterface* getVisualRenderer(void);
    UserInputManagerInterface* getUserInputManager(void);
    ResourceManagerInterface* getResourceManager();
    ClockManagerInterface* getClockManager(void);

private:
    AudioRendererInterface* audioRenderer;
    VisualRendererInterface* visualRenderer;
    UserInputManagerInterface* userInputManager;
    ResourceManagerInterface* resourceManager;
    ClockManagerInterface* clockManager;
};
