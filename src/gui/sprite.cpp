#include "sprite.h"

int Sprite::getX() {
    return this->x;
}

void Sprite::setX(int xNum) {
    this->x = xNum;
}

int Sprite::getY() {
    return 0;
}

void Sprite::setY(int yNum) {
    this->y = yNum;
}

void Sprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->x - App::width()/2, this->y - App::height()/2 - 12), Color::white); // TODO
}

std::ostream& operator<<(std::ostream &strm, const Sprite &sprite) {
    return strm << "X: " << sprite.x << ", Y: " << sprite.y;
}

void Sprite::load(int xNum, int yNum, const String& texturePath) {
    this->x = xNum;
    this->y = yNum;
    this->texture = Texture::create(texturePath);
}
