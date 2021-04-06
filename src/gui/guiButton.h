#ifndef CHESS2_GUIBUTTON_H
#define CHESS2_GUIBUTTON_H

#include <blah.h>
#include "sprite.h"

class GuiButton : public Sprite {
private:
    int width, height;
    TextureRef idleTex, pressedTex;
    void updateTouched();
    bool overlapsPoint(int x, int y);
public:
    bool touched;
    GuiButton(int x, int y, int width, int height, const String& idleTex, const String& pressedTex);
    void setWidth(int widthNum);
    void setHeight(int heigthNum);
    void update();
    bool isClicked();
    void draw(Batch *batch) override;
};


#endif //CHESS2_GUIBUTTON_H
