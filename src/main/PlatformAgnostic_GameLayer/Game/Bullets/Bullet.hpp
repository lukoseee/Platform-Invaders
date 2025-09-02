#pragma once

#include "../Entity.hpp"
#include <string>
#include "../../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

/*
 Class representing both player and enemy bullets
 */
class Bullet : public Entity {
public:
    Bullet(int startX, int startY, const std::string& owner);
    virtual ~Bullet();

    void update() override;
    void render(VisualRendererInterface* renderer) override;

    std::string getOwnerType() const;
    void setOwnerType(const std::string& owner);

    // Setters and getters for animation frames
    void setImageFrame0(ImageInfo* img);
    ImageInfo* getImageFrame0() const;
    void setImageFrame1(ImageInfo* img);
    ImageInfo* getImageFrame1() const;
    void setCurrentRenderedImage(ImageInfo* img);
    ImageInfo* getCurrentRenderedImage() const;

private:
    std::string ownerType;

    // Animation members
    int animationCounter;
    int animationThreshold;  // Use a constant (e.g., BULLET_ANIMATION_THRESHOLD) defined in Constants.hpp
    bool animationToggle;
    ImageInfo* imageFrame0;
    ImageInfo* imageFrame1;
    ImageInfo* currentRenderedImage;
};
