#pragma once

#include <Cocoa/Cocoa.h>
#include <unordered_map>

#include "AppDelegate.hpp"
#include "SpriteView.hpp"
#include "../../../AbstractionLayer/OtherInterfaces/VisualRendererInterface.hpp"
#include "../../../AbstractionLayer/Util/ImageInfo.hpp"

using namespace std;

/*
 See VisualRendererInterface for class description.
 
 Stores a mapping of Images to SpriteViews, to monitor what is being rendered
 to the window. Handles this conversion of Images (abstraction layer object)
 to SpriteViews (Cocoa graphical objects) to process and update visuals
 */
class CocoaRenderer : public VisualRendererInterface {
public:
    CocoaRenderer();
    ~CocoaRenderer();
    
    void createWindow(int, int, std::string, bool) override;
    void closeWindow() override;
    void renderImage(ImageInfo*, int, int) override;
    void moveRenderedImage(ImageInfo*, int, int) override;
    void removeImage(ImageInfo*) override;
    void updateDisplay() override;
    
private:
    unordered_map<ImageInfo*, SpriteView*>* mRenderedImages;
    AppDelegate* mAppDelegate;
};
