#include "sprite.h"

int Sprite::getX() const {
    return this->x;
}

void Sprite::setX(int xNum) {
    this->x = xNum;
}

int Sprite::getY() const {
    return this->y;
}

void Sprite::setY(int yNum) {
    this->y = yNum;
}

std::ostream& operator<<(std::ostream &strm, const Sprite &sprite) {
    return strm << "X: " << sprite.x << ", Y: " << sprite.y;
}

void Sprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->getX(), this->getY()));
}
