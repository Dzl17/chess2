#include "GuiButton.h"

GuiButton::GuiButton() {
    this->width = 0;
    this->height = 0;
    this->touched = false;
}

void GuiButton::setWidth(int widthNum) {
    this->width = widthNum;
}

void GuiButton::setHeight(int heigthNum) {
    this->height = heigthNum;
}

void GuiButton::load(int xNum, int yNum, int widthNum, int heightNum, const String& idleTexPath, const String& pressedTexPath) {
    this->setX(xNum);
    this->setY(yNum);
    this->width = widthNum;
    this->height = heightNum;
    this->idleTex = Texture::create(idleTexPath);
    this->pressedTex = Texture::create(pressedTexPath);
}

void GuiButton::update() {
    this->updateTouched();
}

void GuiButton::draw(Batch *batch) {
    if (!this->touched) batch->tex(this->pressedTex, Vec2(this->getX(), this->getY()), Color::white);
    else batch->tex(this->idleTex, Vec2(this->getX(), this->getY()), Color::white);
}

void GuiButton::updateTouched() {
    Vec2 mouse = Input::mouse_draw();
    int x = (int) mouse.x;
    int y = (int) mouse.y;
    this->touched = this->overlapsPoint(x, y);
}

bool GuiButton::isClicked() {
    Vec2 mouse = Input::mouse_draw();
    return this->overlapsPoint((int) mouse.x, (int) mouse.y) && Input::pressed(MouseButton::Left);
}

bool GuiButton::overlapsPoint(int x, int y) {
    return this->getX() <= x && this->getX() + this->width >= x && this->getY() <= y && this->getY() + this->height >= y;
}

