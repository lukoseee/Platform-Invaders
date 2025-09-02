#include "PlatformInterface.hpp"

#if defined(_WIN32)
   /* #include "../OS_SpecificCode/WINDOWS/Direct2dRenderer.hpp"
    #include "../OS_SpecificCode/WINDOWS/Direct2dAudio.hpp"
    #include "../OS_SpecificCode/WINDOWS/WindowsClockManager.hpp"*/
#define WIN32_LEAN_AND_MEAN
    
    #include "../../OS_SpecificCode/WINDOWS/ClockManager/WindowsClockManager.hpp"
    #include "../../OS_SpecificCode/WINDOWS/ResourceManager/WindowsResourceManager.hpp"
    #include "../../OS_SpecificCode/WINDOWS/Visuals/D2dRenderer.hpp"
    #include "../../OS_SpecificCode/WINDOWS/UserInput/WindowsUserInputManager.hpp"
    #include "../../OS_SpecificCode/WINDOWS/Audio/D2dAudio.hpp"
#elif defined(__APPLE__)
    #include "../../OS_SpecificCode/MAC/Audio/CoreAudio.hpp"
    #include "../../OS_SpecificCode/MAC/Visuals/CocoaRenderer.hpp"
    #include "../../OS_SpecificCode/MAC/UserInput/MacUserInputManager.hpp"
    #include "../../OS_SpecificCode/MAC/ClockManager/MacClockManager.hpp"
    #include "../../OS_SpecificCode/MAC/ResourceManager/MacResourceManager.hpp"
#endif

PlatformInterface::PlatformInterface() {
	// Conditionaly construct correct delegates for each platform
    #if defined(_WIN32)
        visualRenderer = new D2dRenderer();
        userInputManager = WindowsUserInputManager::getInstance();
        clockManager = new WindowsClockManager();
        resourceManager = new WindowsResourceManager();
        audioRenderer = new D2dAudio();
    
    #elif defined(__APPLE__)
        audioRenderer = new CoreAudio();
        visualRenderer = new CocoaRenderer();
        userInputManager = new MacUserInputManager();
        clockManager = new MacClockManager();
        resourceManager = new MacResourceManager();
    #endif
}

// delegate getters

AudioRendererInterface* PlatformInterface::getAudioRenderer() {    return audioRenderer;
}

VisualRendererInterface* PlatformInterface::getVisualRenderer() {
    return visualRenderer;
}

UserInputManagerInterface* PlatformInterface::getUserInputManager() {
    return userInputManager;
}

ResourceManagerInterface* PlatformInterface::getResourceManager() {
    return resourceManager;
}

ClockManagerInterface* PlatformInterface::getClockManager() {
    return clockManager;
}

