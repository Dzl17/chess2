#ifndef CHESS2_GUIBUTTON_H
#define CHESS2_GUIBUTTON_H

#include <blah.h>
#include "sprite.h"

class GuiButton : public Sprite {
private:
    int width, height;
    TextureRef idleTex, pressedTex;
    void updateTouched();
public:
    bool touched;
    GuiButton();
    void setWidth(int widthNum);
    void setHeight(int heigthNum);
    void update() override;
    void load(int xNum, int yNum, int width, int height, const String& idleTex, const String& pressedTex);
    void draw(Batch *batch) override;
};


#endif //CHESS2_GUIBUTTON_H
