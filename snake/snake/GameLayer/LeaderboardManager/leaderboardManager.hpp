#pragma once

#include <list>

#include "../Util/util.hpp"
#include "../constants.hpp"
#include "../Renderer/renderer.hpp"
#include "../../Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "../guiManagerInterface.hpp"

class LeaderboardManager : GUIManagerInterface {
public:
    LeaderboardManager(PlatformInterface*, Renderer*);
    ~LeaderboardManager();

    void initalise() override;
    GUIState loop() override;
    void cleanUp() override;

private:
    std::list<ImageInfo*> constructName(std::string);
    std::list<ImageInfo*> constructScore(std::string);

    std::list<ImageInfo*> imgBuff;
    std::list<ImageInfo*> nameImages;
    std::list<ImageInfo*> scoreImages;
    ImageInfo* leaderboardScreen;
};


