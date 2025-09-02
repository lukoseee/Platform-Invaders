#pragma once

#include "../Entity.hpp"
#include <array>
class VisualRendererInterface; // Forward declaration

class Shield : public Entity {
public:
    Shield(int startX, int startY,
           ImageInfo* fullHPImage,
           ImageInfo* hp3Image,
           ImageInfo* hp2Image,
           ImageInfo* hp1Image);
    virtual ~Shield();

    void update() override;
    void render(VisualRendererInterface* renderer) override;

    ImageInfo* getCurrentRenderedImage() const;
    void setCurrentRenderedImage(ImageInfo* img);
    
    bool isDead();
    void decrementHealth();

private:
    // Index 4 => full health, down to 1 => minimal health, 0 => nullptr
    int health;
    std::array<ImageInfo*, 5> shieldSprites;
    ImageInfo* currentRenderedImage;
};
