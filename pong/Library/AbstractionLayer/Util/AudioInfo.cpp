#include "AudioInfo.hpp"

// Constructor definition
AudioInfo::AudioInfo(const std::string& filePath) : filePath(filePath) {}

// Getter method - returns the file path
std::string AudioInfo::getFilePath() {
    return filePath;
}

// Setter method - updates the file path
void AudioInfo::setFilePath(const std::string& newFilePath) {
    filePath = newFilePath;
}

