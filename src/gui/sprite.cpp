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

std::ostream& operator<<(std::ostream &strm, const Sprite &sprite) {
    return strm << "X: " << sprite.x << ", Y: " << sprite.y;
}
