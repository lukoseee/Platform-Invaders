#include "../../../AbstractionLayer/OtherInterfaces/ResourceManagerInterface.hpp"
#include <string>

/*
 See ResourceManagerInterface for class description
 */
class MacResourceManager : public ResourceManagerInterface{
public:
    ImageInfo* makeImage(std::string token, int width, int height, bool visible) override;
    AudioInfo* makeAudio(std::string token) override;

protected:
    std::string getBuildPathForResource(std::string resource) override;
};
