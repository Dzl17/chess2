#include "draggablePieceSprite.h"

bool DraggablePieceSprite::grabFlag = false;
char *DraggablePieceSprite::formBuffer = new char[FORM_LENGTH];

bool rectCollMouse(int x, int y, Vec2 m);
int getCollidedIndex();

DraggablePieceSprite::DraggablePieceSprite(int x, int y, int id, const String& texturePath) {
    this->setX(x);
    this->setY(y);
    this->ogX = x;
    this->ogY = y;
    this->id = id;
    this->currIndex = -1;
    this->grabbed = false;
    this->texture = Texture::create(texturePath);
    for (int i = 0; i < FORM_LENGTH; i++) {
        if (i != 9) formBuffer[i] = 'e';
        else formBuffer[i] = 'N';
    }
}

void DraggablePieceSprite::resetFormBuffer()
{
    for (int i = 0; i < FORM_LENGTH; i++) {
        if (i != 9) formBuffer[i] = 'e';
        else formBuffer[i] = 'N';
    }
}

void DraggablePieceSprite::update() {
    Vec2 m = Input::mouse();
    if(     rectCollMouse(this->getX(), this->getY(), m) &&
            Input::down(MouseButton::Left) &&
            !this->grabbed && !grabFlag) {
        this->grabbed = true;
        grabFlag = true;
    }

    if (this->grabbed) {
        this->setX((int) m.x - 32);
        this->setY((int) m.y - 32);
        if (Input::released(MouseButton::Left)) {
            int index = getCollidedIndex();
            if (index != -1 && formBuffer[index] == 'e') {
                if (this->currIndex != -1) formBuffer[currIndex] = 'e';
                formBuffer[index] = pieceLetter(this->id);
                this->setX((int) collisionPositions[getCollidedIndex()].x);
                this->setY((int) collisionPositions[getCollidedIndex()].y);
                this->currIndex = index;
            } else {
                formBuffer[this->currIndex] = 'e';
                this->currIndex = -1;
                this->setX(this->ogX);
                this->setY(this->ogY);
            }
            this->grabbed = false;
            grabFlag = false;
        }
    }
}

int DraggablePieceSprite::getId() const {
    return this->id;
}

void DraggablePieceSprite::setCurrIndex(int i) {
    this->currIndex = i;
}

void loadCollisionPositions()
{
    int x = 544;
    int y = 104;
    for (int i = 0; i < FORM_LENGTH; i++) {
        collisionPositions[i] = Vec2(x, y);
        if ((i+1)%3 == 0) {
            x = 544;
            y += 64;
        } else {
            x += 64;
        }
    }
}

bool rectCollMouse(int x, int y, Vec2 m)
{
    return  x <= (int)m.x &&
            x + 64 >= (int)m.x &&
            y <= (int)m.y &&
            y + 64 >= (int)m.y;
}

int getCollidedIndex()
{
    for (int i = 0; i < FORM_LENGTH; i++) {
        if (rectCollMouse((int) collisionPositions[i].x, (int) collisionPositions[i].y, Input::mouse())){
            if (i != 9) return i;
        }
    }
    return -1;
}