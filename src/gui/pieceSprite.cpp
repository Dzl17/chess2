#include "pieceSprite.h"

PieceSprite::PieceSprite(int x, int y, const String& texturePath) {
    this->setX(x);
    this->setY(y);
    this->texture = Texture::create(texturePath);
}

void PieceSprite::update() {

}

void PieceSprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->getX(), this->getY()));
}

