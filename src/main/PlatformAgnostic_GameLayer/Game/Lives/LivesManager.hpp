#pragma once
#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../GameManagerInterface.hpp"
#include <vector>
#include "../../Constants.hpp"

/*
 Manager class to handle the maintaing and rendering of the player's lives
 */
class LivesManager : public GameManagerInterface{
public:
    LivesManager(VisualRendererInterface*, ResourceManagerInterface*);
    ~LivesManager();
    
    void updateAndRender() override;
    
    void initalise();
    void resetLives();
    void decrementLives();
    int getLives();
    

private:
    void clearRenderedIcons();
    
    ImageInfo* livesText; // Background image (e.g., "lives.png").
    int lives;
    int lastRenderedLives;
    std::vector<ImageInfo*> renderedLifeIcons; // Keeps track of rendered life icons for proper removal.
};
