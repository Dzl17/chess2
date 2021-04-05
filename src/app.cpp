#include <blah.h>
#include <windows.h>
#include "content.h"
extern "C" {
    #include "game/chess2.h"
}

using namespace Blah;

bool fullscreen = false;
bool inMenu = false;

Batch batch;

Game game;
std::vector<StaticSprite> staticSprites;
std::vector<GuiButton> buttonSprites;
std::vector<PieceSprite> pieceSprites;

void startup()
{
    startGame(&game, 1,1);
    Assets::load(&staticSprites, &buttonSprites, &pieceSprites, game);
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch.push_matrix(transform);

    //batch.rect(Rect(-32, -32, 64, 64), Color::red);
    Assets::render(&staticSprites, &buttonSprites, &pieceSprites, &batch, game);

    batch.pop_matrix();

    batch.render();
    batch.clear();
}

void update()
{
    if (Input::pressed(Key::P)) PlaySound(TEXT("../data/sound.wav"), nullptr, SND_FILENAME);
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    if (buttonSprites[0].isClicked() || Input::pressed(Key::H)) staticSprites[1].swapActive(); // TODO no funciona bien en pantalla completa
    if (buttonSprites[1].isClicked() || Input::pressed(Key::Escape)) App::exit();

    if (inMenu) Assets::updateMenu(&staticSprites, &buttonSprites, &pieceSprites);
    else Assets::updateGame(&staticSprites, &buttonSprites, &pieceSprites, &game);
}

void dispose()
{
    batch.dispose();
}

int main()
{
    Config config;
    config.name = "Chess 2";
    config.width = 1280;
    config.height = 720;
    config.on_startup = startup;
    config.on_update = update;
    config.on_render = render;
    config.on_shutdown = dispose;
    config.target_framerate = 60;

    App::run(&config);
    return 0;
}