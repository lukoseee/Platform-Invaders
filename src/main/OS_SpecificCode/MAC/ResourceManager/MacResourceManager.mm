#include "MacResourceManager.hpp"

#import "Cocoa/Cocoa.h"

ImageInfo* MacResourceManager::makeImage(std::string token, int width, int height, bool visible) {
    return new ImageInfo(getBuildPathForResource(token + ".png"), width, height, visible);
}

std::string MacResourceManager::getBuildPathForResource(std::string resource) {
    auto delimPos = resource.find(".");
    std::string res = resource.substr(0, delimPos);
    std::string ext = resource.substr(delimPos + 1);
    
    NSString* nsRes = [NSString stringWithUTF8String:res.c_str()];
    NSString* nsExt = [NSString stringWithUTF8String:ext.c_str()];
    
    NSString* nsFullPath = [[NSBundle mainBundle] pathForResource:nsRes ofType:nsExt];
    if (!nsFullPath) {
        throw std::runtime_error("Missing resource: " + resource);
    }
    return [nsFullPath UTF8String];
}

AudioInfo* MacResourceManager::makeAudio(std::string token) {
    return new AudioInfo(getBuildPathForResource(token + ".wav"));
}

