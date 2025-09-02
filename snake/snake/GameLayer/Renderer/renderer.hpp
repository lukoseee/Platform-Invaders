#pragma once

#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../Util/util.hpp"

// simple wrapper class for VisualRendererInterface, handles coordinate
// conversions
class Renderer {
public:
    Renderer(VisualRendererInterface* v);
    void render(ImageInfo* img, Position pos);
    void remove(ImageInfo* img);
    
private:
    VisualRendererInterface* v;
};
