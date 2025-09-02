#pragma once

#include <unordered_map>
#include <string>

class SoundManager {
private:
    std::unordered_map<int, std::string> soundMap;
public:
    void addSound(int id, const std::string& filePath) {
        soundMap[id] = filePath;
    }

    std::string getSoundFilePath(int id) {
        return soundMap.count(id) ? soundMap[id] : "";
    }
};
