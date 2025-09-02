#pragma once

#include <string>


/*
 ImageInfo is a utility class to provide abstracted interactions between the game
 layer and abstraction layer.
 
 Game layers are intended to instantiate these image objects and utilise them
 to communicate with the abstraction layer to render graphics to the screen.
 
 This class works in tandem with the ResourceManagerInterface and
 VisualRendererInterface
*/
class ImageInfo {
public:
    ImageInfo(std::string filePath, int width, int height, bool visible);
    
    // getters
    std::string getFilePath(void);
    int getWidth(void);
    int getHeight(void);
    bool isVisible(void);
    
    //setters
    void setFilePath(std::string filePath);
    void setWidth(int width);
    void setHeight(int height);
    void setVisible(bool visible);
    
private:
    std::string filePath;
    int width;
    int height;
    bool visible;
};

