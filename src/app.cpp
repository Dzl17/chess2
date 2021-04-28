#include <blah.h>
#include <unordered_map>
#include "content.h"
#include "dbmanager.h"
extern "C" {
    #include "game/chess2.h"
}

using namespace Blah;

bool fullscreen = false;
int currentMode = 0;

Batch *batch;
DBManager *dbManager;
FormationSet formSet;

Game game;
UmStatics staticSprites;
UmButtons buttonSprites;
VcPieces pieceSprites;
VcNexuses nexusSprites;

void startup()
{
    /////////////////////////TEMP/////////////////////////
    formSet.index = 0;
    formSet.size = 4;
    formSet.forms = new char*[formSet.size];
    formSet.forms[0] = (char*) "ssssggeeeNeeeeeaaawww";
    formSet.forms[1] = (char*) "esgesewweNeweaeasaseg";
    formSet.forms[2] = (char*) "ewsseageeNaweegwsasee";
    formSet.forms[3] = (char*) "ssgweewweNeeaaeaeessg";
    /////////////////////////TEMP/////////////////////////

    batch = new Batch;
    Assets::load(&staticSprites, &buttonSprites, &pieceSprites, &nexusSprites, &game, &currentMode, &formSet);
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch->push_matrix(transform);

    Assets::render(staticSprites, buttonSprites, &pieceSprites, &nexusSprites, game, &currentMode, &formSet, batch);

    batch->pop_matrix();
    batch->render();
    batch->clear();
}

void update()
{
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    Assets::update(staticSprites, buttonSprites, &pieceSprites, &nexusSprites, &game, &currentMode, &formSet);
}

void dispose()
{
    for (auto & staticSprite:staticSprites) delete staticSprite.second;
    for (auto & button:buttonSprites) delete button.second;
    batch->dispose();
    delete batch;
    delete dbManager;
}

int main()
{
    dbManager = new DBManager((char*) "../data/database.db");
    Login::runSetup(); // Inicio de sesión, base de datos

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