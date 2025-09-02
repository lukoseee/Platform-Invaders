#pragma once

#include "../../../AbstractionLayer/OtherInterfaces/ResourceManagerInterface.hpp"

/*
 See ResourceManagerInterface for class description
 */

class WindowsResourceManager : public ResourceManagerInterface {
public:
    ImageInfo* makeImage(std::string, int, int, bool) override; 
    AudioInfo* makeAudio(std::string) override;

protected:
    std::string getBuildPathForResource(std::string resource) override;
};
