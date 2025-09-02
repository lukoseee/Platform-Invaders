#pragma once

#include <list>

#include "../GUIInterface.hpp"

class LeaderboardController: GUIInterface{
public:
    LeaderboardController(PlatformInterface*);
    ~LeaderboardController();
    
    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;
    
private:
    std::list<ImageInfo*> constructName(std::string);
    std::list<ImageInfo*> constructScore(std::string);
    
    std::list<ImageInfo*> nameImages;
    std::list<ImageInfo*> scoreImages;
    std::list<ImageInfo*> imgBuff;
    ImageInfo* leaderboardScreen;
};
