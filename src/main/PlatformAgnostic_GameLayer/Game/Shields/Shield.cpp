#include "Shield.hpp"
#include "../../../AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"
#include "../../Constants.hpp"
#include <algorithm>

Shield::Shield(int startX, int startY,
               ImageInfo* fullHPImage,
               ImageInfo* hp3Image,
               ImageInfo* hp2Image,
               ImageInfo* hp1Image)
    : currentRenderedImage(nullptr)
{
    setPosition({startX, startY});
    health = SHIELD_INITIAL_HEALTH;

    shieldSprites[4] = fullHPImage;
    shieldSprites[3] = hp3Image;
    shieldSprites[2] = hp2Image;
    shieldSprites[1] = hp1Image;
    shieldSprites[0] = nullptr;

    setImage(shieldSprites[4]);
    currentRenderedImage = getImage();
}

Shield::~Shield()
{
    for(ImageInfo* img : shieldSprites) {
        delete img;
    }
}

void Shield::update()
{
    if (health > 0) {
        int key = std::min(health, SHIELD_INITIAL_HEALTH);
        setImage(shieldSprites[key]);
    }
}

void Shield::render(VisualRendererInterface* renderer)
{
    if (getImage() == nullptr) {
        return;
    }
    if (currentRenderedImage != getImage()) {
        if (currentRenderedImage) {
            renderer->removeImage(currentRenderedImage);
        }
        renderer->renderImage(getImage(), getPosition().x, getPosition().y);
        currentRenderedImage = getImage();
    } else {
        renderer->moveRenderedImage(getImage(), getPosition().x, getPosition().y);
    }
}

ImageInfo* Shield::getCurrentRenderedImage() const
{
    return currentRenderedImage;
}

void Shield::setCurrentRenderedImage(ImageInfo* img)
{
    currentRenderedImage = img;
}

bool Shield::isDead() {
    return health == 0;
}

void Shield::decrementHealth() {
    health--;
}
