#ifndef CHESS2_DRAGGABLEPIECESPRITE_H
#define CHESS2_DRAGGABLEPIECESPRITE_H

#include "sprite.h"

class DraggablePieceSprite :  public Sprite{
private:
    int ogX, ogY, id, currIndex; // TODO newX/newY para comodidad
public:
    DraggablePieceSprite(int x, int y, int id, const String& texturePath);

    bool grabbed;
    static bool grabFlag;
    static char *formBuffer;

    static void resetFormBuffer();

    void update() override;
    void draw(Batch *batch) override;
};

static Vec2 collisionPositions[FORM_LENGTH];
void loadCollisionPositions();

#endif