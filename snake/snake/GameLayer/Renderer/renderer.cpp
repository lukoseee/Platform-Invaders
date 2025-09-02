#include "renderer.hpp"
#include "../constants.hpp"

Renderer::Renderer(VisualRendererInterface* v) {
    this->v = v;
}

void Renderer::render(ImageInfo* img, Position pos) {
    v->renderImage(img, pos.x * CELL_SIZE, pos.y * CELL_SIZE);
    //std::cout << "Address in game layer: " << img << std::endl;
}

void Renderer::remove(ImageInfo* img) {
    v->removeImage(img);
}
