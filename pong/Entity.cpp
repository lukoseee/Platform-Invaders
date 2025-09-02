#include "Entity.hpp"

Entity::Entity()
    : health(0), image(nullptr)
{
    pos = {0, 0};
}

Entity::~Entity()
{
}

Position Entity::getPosition() const
{
    return pos;
}

void Entity::setPosition(const Position& p)
{
    pos = p;
}

Position Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(const Position& v)
{   
    velocity = v;
}

int Entity::getHealth() const
{
    return health;
}

void Entity::setHealth(int h)
{
    health = h;
}

ImageInfo* Entity::getImage() const
{
    return image;
}

void Entity::setImage(ImageInfo* img)
{
    image = img;
}
