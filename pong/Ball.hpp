#pragma once

#include "Entity.hpp"

class VisualRendererInterface;
class ImageInfo;

class Ball : public Entity {
public:

    Ball(float startX, float startY);
    virtual ~Ball();

    void update() override;
    void render(VisualRendererInterface* renderer) override;
	void handleInput(const std::string& input) override;

    void bounceVertical();
	void bounceHorizontal();

private:
};
