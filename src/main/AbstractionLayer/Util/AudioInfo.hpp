#pragma once

#include <string>

class AudioInfo {
private:
    std::string filePath;  // Stores the file path of the audio file

public:
    // Constructor
    AudioInfo(const std::string& filePath);

    // Getter method
    std::string getFilePath();

    // Setter method
    void setFilePath(const std::string& newFilePath);
};
