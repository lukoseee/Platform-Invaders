#include "ShieldManager.hpp"

ShieldManager::ShieldManager(VisualRendererInterface* visualRenderer, ResourceManagerInterface* resourceMan) {
    this->visualRenderer = visualRenderer;
    this->resourceMan = resourceMan;
}

ShieldManager::~ShieldManager() {
    for (auto it = shields.begin(); it != shields.end(); ) {
        Shield* shield = *it;
        it++;
        removeShield(shield);
    }
}

void ShieldManager::initalise() {
    createShield(SHIELD1_X, SHIELD1_Y);
    createShield(SHIELD2_X, SHIELD2_Y);
    createShield(SHIELD3_X, SHIELD3_Y);
    createShield(SHIELD4_X, SHIELD4_Y);
}

void ShieldManager::updateAndRender() {
    for (auto it = shields.begin(); it != shields.end(); ) {
        Shield* shield = *it;
        it++;
        
        if(shield->isDead()) {
            removeShield(shield);
            continue;
        }
        
        
        shield->update();
        shield->render(visualRenderer);
    }
}

void ShieldManager::damageShield(Shield* shield) {
    shield->decrementHealth();
}

void ShieldManager::removeShield(Shield* shield) {
    shields.remove(shield);
    visualRenderer->removeImage(shield->getImage());
    delete shield;
}

std::list<Shield*> ShieldManager::getShields() {
    return shields;
}

std::array<ImageInfo*, 4> ShieldManager::loadShieldImages(ShieldBlockType type) {
    std::array<ImageInfo*, 4> images;
    switch (type) {
        case ShieldBlockType::EMPTY:
            images.fill(nullptr);
            break;
        case ShieldBlockType::UPPER_LEFT:
            images[0] = resourceMan->makeImage("0_shield_sprite_upperleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[1] = resourceMan->makeImage("1_shield_sprite_upperleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[2] = resourceMan->makeImage("2_shield_sprite_upperleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[3] = resourceMan->makeImage("3_shield_sprite_upperleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            break;
        case ShieldBlockType::UPPER_RIGHT:
            images[0] = resourceMan->makeImage("0_shield_sprite_upperright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[1] = resourceMan->makeImage("1_shield_sprite_upperright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[2] = resourceMan->makeImage("2_shield_sprite_upperright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[3] = resourceMan->makeImage("3_shield_sprite_upperright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            break;
        case ShieldBlockType::LOWER_LEFT:
            images[0] = resourceMan->makeImage("0_shield_sprite_lowerleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[1] = resourceMan->makeImage("1_shield_sprite_lowerleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[2] = resourceMan->makeImage("2_shield_sprite_lowerleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[3] = resourceMan->makeImage("3_shield_sprite_lowerleft", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            break;
        case ShieldBlockType::LOWER_RIGHT:
            images[0] = resourceMan->makeImage("0_shield_sprite_lowerright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[1] = resourceMan->makeImage("1_shield_sprite_lowerright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[2] = resourceMan->makeImage("2_shield_sprite_lowerright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[3] = resourceMan->makeImage("3_shield_sprite_lowerright", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            break;
        case ShieldBlockType::SQUARE:
        default:
            images[0] = resourceMan->makeImage("0_shield_sprite_square", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[1] = resourceMan->makeImage("1_shield_sprite_square", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[2] = resourceMan->makeImage("2_shield_sprite_square", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            images[3] = resourceMan->makeImage("3_shield_sprite_square", SHIELD_IMAGE_WIDTH, SHIELD_IMAGE_HEIGHT, true);
            break;
    }
    return images;
}

void ShieldManager::createShield(int startX, int startY) {
    // Define the layout for a single shield block (SHIELD_BLOCK_ROWS x SHIELD_BLOCK_COLS).
    static const int rows = SHIELD_BLOCK_ROWS;
    static const int cols = SHIELD_BLOCK_COLS;
    ShieldBlockType shieldLayout[rows][cols] = {
        { ShieldBlockType::SQUARE,    ShieldBlockType::EMPTY,       ShieldBlockType::EMPTY,       ShieldBlockType::SQUARE },
        { ShieldBlockType::SQUARE,    ShieldBlockType::LOWER_LEFT,  ShieldBlockType::LOWER_RIGHT, ShieldBlockType::SQUARE },
        { ShieldBlockType::UPPER_LEFT,ShieldBlockType::SQUARE,      ShieldBlockType::SQUARE,      ShieldBlockType::UPPER_RIGHT }
    };

    // For each block in the shield layout, create and add a Shield block.
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int xPos = startX + col * SHIELD_IMAGE_WIDTH;
            int yPos = startY + row * SHIELD_IMAGE_HEIGHT;
            ShieldBlockType blockType = shieldLayout[row][col];

            // Load images for the shield block.
            std::array<ImageInfo*, 4> shieldImages = loadShieldImages(blockType);
            if (shieldImages[0] == nullptr) {
                continue;  // Skip blocks with no image.
            }

            Shield* shieldBlock = new Shield(xPos, yPos,
                                             shieldImages[0],
                                             shieldImages[1],
                                             shieldImages[2],
                                             shieldImages[3]);
            // Immediately render the shield block.
            visualRenderer->renderImage(shieldBlock->getImage(), xPos, yPos);
            shields.push_back(shieldBlock);
        }
    }
}
