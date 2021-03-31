#include "pieceSprite.h"

PieceSprite::PieceSprite(int x, int y, String& texturePath) {
    this->setX(x);
    this->setY(y);
    this->texture = Texture::create(texturePath);
}

void PieceSprite::update() {

}

void PieceSprite::draw(Batch *batch) {

}

