#pragma once

#include "../GUIInterface.hpp"
#include <vector>

class MenuController : public GUIInterface{
public:
    MenuController(PlatformInterface*);
    ~MenuController();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;
    
private:
    void renderArrow();
    
    ImageInfo* background;
    ImageInfo* arrow;
    std::vector<int> arrowPositions;
    int arrowPositionPtr;
};
