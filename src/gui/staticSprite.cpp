#include "staticSprite.h"

StaticSprite::StaticSprite(int x, int y, const String& texturePath, bool active)
{
    this->setX(x);
    this->setY(y);
    this->active = active;
    this->texture = Texture::create(texturePath);
}

void StaticSprite::swapActive() {
    this->active = !this->active;
}

void StaticSprite::draw(Batch *batch) {
    if (this->active) batch->tex(this->texture, Vec2(this->getX(), this->getY()), Color::white);
}

void StaticSprite::update() {

}

