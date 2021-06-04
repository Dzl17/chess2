#ifndef CHESS2_PIECESPRITE_H
#define CHESS2_PIECESPRITE_H

#include "sprite.h"
extern "C"{
    #include "../game/game.h"
}

class PieceSprite : public Sprite {
private:
    Game *gameRef; // Referencia a game
    bool overlapsMouse();
    static bool mouseOverlapsPoint(int x, int y);
    bool touched;
public:
    Vec2 focus;
    static int selectedPiece;
    static bool multiplayer;
    int id, hp;
    bool active;
    int getPieceCode() const;
    PieceSprite(int x, int y, int id, const String& texturePath, Game *gameRef);

    enum State {
        IDLE, CHOOSING, MOVING, ATTACKING
    };
    State state;

    enum AttackDir {N, NW, W, SW, S, SE, E, NE, C}; // Direcciones de ataque
    AttackDir attackDir;
    void setAttackDir(Vec2 origin, Vec2 destiny); // Calcular direción de ataque
    double attack_timer; // Temporizador de animación
    Vec2 positionBuffer; // Posición de retorno
    void animateAttack();

    void update() override;
    void draw(Batch *batch) override;
    std::vector<Vec2> getMovePositions(int data[7][11]);
    std::vector<Vec2> getAttackPositions(int data[7][11]);
};


#endif //CHESS2_PIECESPRITE_H
