#pragma once

#include <string>
#include "../../AbstractionLayer/Util/ImageInfo.hpp"
#include "../Constants.hpp"
#include "../../AbstractionLayer/PlatformInterface/PlatformInterface.hpp"

// Forward declaration of VisualRendererInterface
class VisualRendererInterface;

struct Position {
    int x;
    int y;
};

class Entity {
public:
    // Pure virtual methods for entity behavior
    virtual void update() = 0;
    virtual void render(VisualRendererInterface* renderer) = 0;

    // Position
    Position getPosition() const;
    void setPosition(const Position& pos);

    // ImageInfo
    ImageInfo* getImage() const;
    void setImage(ImageInfo* img);

protected:
    Position pos;
    ImageInfo* image;
};
