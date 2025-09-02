#include "ImageInfo.hpp"

ImageInfo::ImageInfo(std::string filePath, int width, int height, bool visible) {
    this->filePath = filePath;
    this->width = width;
    this->height = height;
    this->visible = visible;
}

// getters

std::string ImageInfo::getFilePath() {
    return filePath;
}

int ImageInfo::getWidth() {
    return width;
}

int ImageInfo::getHeight() {
    return height;
}

bool ImageInfo::isVisible() {
    return visible;
}

// setters

void ImageInfo::setFilePath(std::string filePath) {
    this->filePath = filePath;
}

void ImageInfo::setWidth(int width) {
    this->width = width;
}

void ImageInfo::setHeight(int height) {
    this->height = height;
}

void ImageInfo::setVisible(bool visible) {
    this->visible = visible;
}
