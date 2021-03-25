#include <blah.h>

using namespace Blah;

Batch batch;
TextureRef gridTex;
TextureRef lionTex;

void startup()
{
    gridTex = Texture::create("../data/img/grid.png");
    lionTex = Texture::create("../data/img/boredlion.png");
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto center = Vec2(App::backbuffer->width(), App::backbuffer->height()) / 2;
    //auto rotation = Time::seconds * Calc::TAU;
    auto transform = Mat3x2::create_transform(center, Vec2::zero, Vec2::one, 0);

    batch.push_matrix(transform);
    //batch.rect(Rect(-32, -32, 64, 64), Color::red);
    batch.tex(gridTex, Vec2(-330, -350), Color::white);
    batch.tex(lionTex, Vec2(-330, -350), Color::white);
    batch.pop_matrix();

    batch.render();
    batch.clear();
}

int main()
{
    Config config;
    config.name = "Chess 2";
    config.width = 1280;
    config.height = 720;
    config.on_startup = startup;
    config.on_render = render;
    config.target_framerate = 60;

    App::run(&config);
    return 0;
}