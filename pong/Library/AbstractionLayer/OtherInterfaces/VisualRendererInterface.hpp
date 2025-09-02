#pragma once

#include "../Util/ImageInfo.hpp"


/*
 VisualRendererInterface provides a platform-agnostic mechanism for the
 game layer to create a window and display graphical elements to the window.
 
 This interface works in tandem with the ImageInfo class to provide suitable
 abstraction.
 
 All required visual effects to produce a basic 2D game can be achieved by the
 methods provded.
 */
class VisualRendererInterface {
public:
    // instantiate a window to display graphics to
    virtual void createWindow(int width, int height, std::string windowName, bool resizeable) = 0;
    
    // close the window if already created
    virtual void closeWindow() = 0;
    
    // render an image for the first time at a given x, y (pixel) location
    virtual void renderImage(ImageInfo* image, int x, int y) = 0;
    
    // move an already rendered image to a new location
    virtual void moveRenderedImage(ImageInfo* image, int x, int y) = 0;
    
    // remove an image from the screen
    virtual void removeImage(ImageInfo* image) = 0;
    
    // process any changes made to the window. Intended to be called at the
    // end of each iteration of a game loop.
    virtual void updateDisplay(void) = 0;
};
