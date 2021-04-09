#include <blah.h>
#include "content.h"
extern "C" {
    #include "game/chess2.h"
}

using namespace Blah;

bool fullscreen = false;
int currentMode = 0;

Batch batch;

Game game;
std::vector<StaticSprite> staticSprites;
std::vector<GuiButton> buttonSprites;
std::vector<PieceSprite> pieceSprites;
std::vector<NexusSprite> nexusSprites;

void startup()
{
    startGame(&game, 1,1);
    Assets::load(&staticSprites, &buttonSprites, &pieceSprites, &nexusSprites, game, &currentMode);
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch.push_matrix(transform);

    Assets::render(&staticSprites, &buttonSprites, &pieceSprites, &nexusSprites, &batch, game, &currentMode);

    batch.pop_matrix();
    batch.render();
    batch.clear();
}

void update()
{
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    Assets::update(&staticSprites, &buttonSprites, &pieceSprites, &nexusSprites, &batch, &game, &currentMode);
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