#include <blah.h>
#include <list>
#include <map>
#include "content.h"
#include "game/chess2.h"

using namespace Blah;

bool fullscreen = false;

Batch batch;

Game game;
std::list<StaticSprite> staticSprites;
std::map<int, GuiButton> buttonSprites;
std::map<int, PieceSprite> pieceSprites;

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
    if (buttonSprites.find(1)->second.isClicked()) App::exit();
}

void shutdown()
{
    batch.dispose();
}

int maian()
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