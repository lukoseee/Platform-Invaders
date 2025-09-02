#include "WindowsResourceManager.hpp"
#include <iostream>
#include <filesystem>
#include <windows.h>

ImageInfo* WindowsResourceManager::makeImage(std::string token, int width, int height, bool visible) {
	//buffer to store path (max path defined in windows api length 256)
	std::string imageName = token + ".png"; 
	return new ImageInfo(getBuildPathForResource(imageName), width, height, visible);
}

std::string WindowsResourceManager::getBuildPathForResource(std::string resource) {

	//buffer to store path (max path defined in windows api length 256)
	char path[MAX_PATH];
	
	//buffer to store path (max path defined in windows api length 256)	
	GetModuleFileNameA(NULL, path, MAX_PATH); 
	
	//buffer to store path (max path defined in windows api length 256)
	std::filesystem::path currentDir = std::filesystem::path(path).parent_path(); 

	for (const auto& entry : std::filesystem::recursive_directory_iterator(currentDir)) { //recursively search for the file within the parent directory
		if (entry.path().filename() == resource) {
			//std::cout << "File found: " << entry.path().string() << std::endl;
			//buffer to store path (max path defined in windows api length 256)
			return entry.path().string(); 
		}
	}

}

AudioInfo* WindowsResourceManager::makeAudio(std::string token) {
	//buffer to store path (max path defined in windows api length 256)
	std::string audioName = token + ".wav"; 
	return new AudioInfo(getBuildPathForResource(audioName));

}