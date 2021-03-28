#include <blah.h>
#include "gui/sprite.h"
#include "gui/GuiButton.h"

using namespace Blah;

Batch batch;
GuiButton testButton;

void startup()
{
    testButton.load(0, 0, 64, 64, "../data/img/boredlion.png", "../data/img/grid.png");

    //Sprites::load();
}

void render()
{
    App::backbuffer->clear(Color::black);

    testButton.update();

    auto center = Vec2(App::backbuffer->width(), App::backbuffer->height()) / 2;
    //auto rotation = Time::seconds * Calc::TAU;
    auto transform = Mat3x2::create_transform(center, Vec2::zero, Vec2::one, 0);

    batch.push_matrix(transform);
    //batch.rect(Rect(-32, -32, 64, 64), Color::red);
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
    //Sprites::clear(); ??
}

int main()
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