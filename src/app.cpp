#include <blah.h>
#include "gui/sprite.h"
#include "gui/GuiButton.h"
#include "gui/staticSprite.h"

using namespace Blah;

bool fullscreen = false;

Batch batch;

StaticSprite background;
GuiButton testButton;

void startup()
{
    testButton.load(32, 16, 192, 64,
                    "../data/img/testButtonIdle.png", "../data/img/testButtonPressed.png");
    background.load(0, 0, "../data/img/background.png");
    //Sprites::load();
}

void render()
{
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    if (testButton.isClicked()) App::exit();

    App::backbuffer->clear(Color::black);

    testButton.update();

    //auto rotation = Time::seconds * Calc::TAU;
    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch.push_matrix(transform);
    //batch.rect(Rect(-32, -32, 64, 64), Color::red);
    background.draw(&batch);
    testButton.draw(&batch);
    batch.pop_matrix();

    batch.render();
    batch.clear();

    //Sprites::update();
    //Sprites::render();
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
    config.on_shutdown = shutdown;
    config.on_render = render;
    config.target_framerate = 60;

    App::run(&config);
    return 0;
}