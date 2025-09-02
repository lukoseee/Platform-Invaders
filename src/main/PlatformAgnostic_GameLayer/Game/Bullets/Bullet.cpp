#include "Bullet.hpp"
#include "../../../AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"
#include "../../Constants.hpp"

Bullet::Bullet(int startX, int startY, const std::string& owner)
    : ownerType(owner),
      animationCounter(0),
      animationThreshold(BULLET_ANIMATION_THRESHOLD),
      animationToggle(false),
      imageFrame0(nullptr),
      imageFrame1(nullptr),
      currentRenderedImage(nullptr)
{
    setPosition({startX, startY});
    setImage(nullptr);
}

Bullet::~Bullet()
{
    delete imageFrame0;
    delete imageFrame1;
    
    if(ownerType == "player")
       delete image;
}

void Bullet::update()
{
    // Update bullet position based on owner type.
    Position p = getPosition();
    if (ownerType == "player") {
        p.y += BULLET_PLAYER_SPEED;
    } else {
        p.y -= BULLET_ENEMY_SPEED;
    }
    setPosition(p);

    // Update bullet animation if both frames are set.
    if (imageFrame0 != nullptr && imageFrame1 != nullptr) {
        animationCounter++;
        if (animationCounter >= animationThreshold) {
            animationToggle = !animationToggle;
            // Toggle between the two animation frames.
            setImage(animationToggle ? imageFrame1 : imageFrame0);
            animationCounter = 0;
        }
    }
}

void Bullet::render(VisualRendererInterface* renderer)
{
    if (getImage() == nullptr) {
        return;
    }
    // If the image has changed, update the rendered image; otherwise, simply move it.
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

std::string Bullet::getOwnerType() const
{
    return ownerType;
}

void Bullet::setOwnerType(const std::string& owner)
{
    ownerType = owner;
}

// Animation frame setters and getters.
void Bullet::setImageFrame0(ImageInfo* img) {
    imageFrame0 = img;
}

ImageInfo* Bullet::getImageFrame0() const {
    return imageFrame0;
}

void Bullet::setImageFrame1(ImageInfo* img) {
    imageFrame1 = img;
}

ImageInfo* Bullet::getImageFrame1() const {
    return imageFrame1;
}

void Bullet::setCurrentRenderedImage(ImageInfo* img) {
    currentRenderedImage = img;
}

ImageInfo* Bullet::getCurrentRenderedImage() const {
    return currentRenderedImage;
}
