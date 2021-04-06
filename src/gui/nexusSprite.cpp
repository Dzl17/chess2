#include "nexusSprite.h"
#include <cmath>

NexusSprite::NexusSprite(int x, int y, const String &texturePath) {
    this->setX(x);
    this->setY(y);
    this->texture = Texture::create(texturePath);
    this->deltaCounter = 0;
}

void NexusSprite::update() {
    this->deltaCounter += Time::delta;
    this->setY((int) (256 + std::sin(deltaCounter * 4) * 5));
}

void NexusSprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->getX(), this->getY()));
}
