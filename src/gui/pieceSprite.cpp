#include "pieceSprite.h"

PieceSprite::PieceSprite(int x, int y, int id, const String& texturePath) {
    this->state = IDLE;
    this->setX(x);
    this->setY(y);
    this->id = id;
    this->active = true;
    this->texture = Texture::create(texturePath);
    this->touched = false;
}

void PieceSprite::update() {
    if (this->touched && this->overlapsMouse() && Input::released(MouseButton::Left)) this->touched = false;
    switch (this->state) {
        case IDLE:
            if (this->overlapsMouse() && Input::pressed(MouseButton::Left) && !this->touched) {
                this->touched = true;
                this->state = CHOOSING;
            }
            break;
        case CHOOSING:
            if (this->overlapsMouse() && Input::pressed(MouseButton::Left) && !this->touched) {
                this->touched = true;
                this->state = IDLE;
            }
            // Colorear espacios
            break;
        case MOVING:
            // Animación de movimiento
            if (!(this->getX() == (int)this->focus.x && this->getY() == (int)this->focus.y)) {
                this->setX(this->getX() + ((int) this->focus.x - this->getX()) * 0.1);
                this->setY(this->getY() + ((int) this->focus.y - this->getY()) * 0.1);
            } else {
                this->state = IDLE;
            }
            break;
        case ATTACKING:
            // Animación de ataque
            break;
    }
}

void PieceSprite::draw(Batch *batch) {
    if (this->active) batch->tex(this->texture, Vec2(this->getX(), this->getY()));
}

void PieceSprite::setFocus(Vec2 focusVal) {
    this->focus = focusVal;
}

bool PieceSprite::overlapsMouse() {
    Vec2 mouse = Input::mouse_draw();
    int x = (int) mouse.x;
    int y = (int) mouse.y;
    return this->getX() <= x && this->getX() + 64 >= x && this->getY() <= y && this->getY() + 64 >= y;
}

void PieceSprite::setCoords(int x, int y) {
    //this->setX();
    //this->setY();
}

