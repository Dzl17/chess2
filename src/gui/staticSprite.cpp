#include "staticSprite.h"

StaticSprite::StaticSprite() = default;

void StaticSprite::load(int x, int y, const String &texturePath) {
    this->setX(x);
    this->setY(y);
    this->texture = Texture::create(texturePath);
}

void StaticSprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->getX(), this->getY()), Color::white);
}

void StaticSprite::update() {

}
