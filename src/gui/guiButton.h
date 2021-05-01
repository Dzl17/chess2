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
    bool touched;
public:
    GuiButton(int x, int y, int width, int height, const String& idleTex, const String& pressedTex);
    bool isClicked();

    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_GUIBUTTON_H
