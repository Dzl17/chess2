#include "draggablePieceSprite.h"

bool DraggablePieceSprite::grabFlag = false;

DraggablePieceSprite::DraggablePieceSprite(int x, int y, const String& texturePath) {
    this->setX(x);
    this->setY(y);
    this->grabbed = false;
    this->texture = Texture::create(texturePath);
}

void DraggablePieceSprite::update() {
    Vec2 m = Input::mouse();
    if(     this->getX() <= (int)m.x &&
            this->getX() + 64 >= (int)m.x &&
            this->getY() <= (int)m.y &&
            this->getY() + 64 >= (int)m.y &&
            Input::down(MouseButton::Left) &&
            !this->grabbed && !grabFlag) {
        this->grabbed = true;
        grabFlag = true;
    }

    if (this->grabbed) {
        this->setX((int) m.x - 32);
        this->setY((int) m.y - 32);
        if (Input::released(MouseButton::Left)) {
            this->grabbed = false;
            grabFlag = false;
        }
    }
}

void DraggablePieceSprite::draw(Batch *batch) {
    batch->tex(this->texture, Vec2(this->getX(), this->getY()));
}