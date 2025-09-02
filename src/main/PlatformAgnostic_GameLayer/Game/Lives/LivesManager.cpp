#include "LivesManager.hpp"
#include "../../Constants.hpp"

// Constructor: Load the "LIVES" text background and the player sprite for life icons.
LivesManager::LivesManager(VisualRendererInterface* visualRenderer, ResourceManagerInterface* resourceMan) {
    this->visualRenderer = visualRenderer;
    this->resourceMan = resourceMan;
    
    lives = PLAYER_INITIAL_LIVES;
    lastRenderedLives = -1;
}

LivesManager::~LivesManager() {
    visualRenderer->removeImage(livesText);
    delete livesText;
    livesText = nullptr;
    
    clearRenderedIcons();
}

void LivesManager::updateAndRender() {
    // dont waste the compute if nothing has changed
    if(lastRenderedLives == lives)
        return;
    
    // remove the current images
    clearRenderedIcons();
    
    // render for the new amount of lives
    for(int i = 0; i < lives; i++) {
        ImageInfo* lifeIcon = resourceMan->makeImage(PLAYER_IMAGE, LIVES_ICON_WIDTH, LIVES_ICON_HEIGHT, true);
        visualRenderer->renderImage(
            lifeIcon,
            LIVES_DISPLAY_X + livesText->getWidth() + LIFE_ICON_OFFSET_X + (i * LIFE_ICON_SPACING),
            LIVES_DISPLAY_Y
        ); // just make the X value a seperate constant? instead of doing all this math. Come back to this
        renderedLifeIcons.push_back(lifeIcon);
    }
    lastRenderedLives = lives;
}

void LivesManager::initalise() {
    // Load the background image for the lives display.
    livesText = resourceMan->makeImage(LIVES_IMAGE, LIVES_TEXT_IMAGE_WIDTH, LIVES_TEXT_IMAGE_HEIGHT, true);
    visualRenderer->renderImage(livesText, LIVES_DISPLAY_X, LIVES_DISPLAY_Y);
    
    updateAndRender();
}

void LivesManager::resetLives() {
    lives = PLAYER_INITIAL_LIVES;
}

void LivesManager::decrementLives() {
    lives--;
}

int LivesManager::getLives() {
    return lives;
}

void LivesManager::clearRenderedIcons() {
    for(ImageInfo* icon : renderedLifeIcons) {
        visualRenderer->removeImage(icon);
        delete icon;
    }
    renderedLifeIcons.clear();
}
