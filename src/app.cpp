#include <blah.h>
#include "content.h"
#include "game/chess2.h"

using namespace Blah;

bool fullscreen = false;

Batch batch;

Game game;
std::vector<StaticSprite> staticSprites;
std::vector<GuiButton> buttonSprites;
std::vector<PieceSprite> pieceSprites;

void startup()
{
    Assets::load(&staticSprites, &buttonSprites, &pieceSprites);
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch.push_matrix(transform);

    //batch.rect(Rect(-32, -32, 64, 64), Color::red);
    Assets::render(&staticSprites, &buttonSprites, &pieceSprites, &batch);

    batch.pop_matrix();

    batch.render();
    batch.clear();
}

void update()
{
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    if (buttonSprites[0].isClicked() || Input::pressed(Key::H)) staticSprites[1].swapActive(); // TODO no funciona bien en pantalla completa
    if (buttonSprites[1].isClicked() || Input::pressed(Key::Escape)) App::exit();
}

void shutdown()
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
    config.on_shutdown = shutdown;
    config.target_framerate = 60;

    App::run(&config);
    return 0;
}