#include "Entity.hpp"

Position Entity::getPosition() const
{
    return pos;
}

void Entity::setPosition(const Position& p)
{
    pos = p;
}

ImageInfo* Entity::getImage() const
{
    return image;
}

void Entity::setImage(ImageInfo* img)
{
    image = img;
}
