#include <blah.h>
#include <unordered_map>
#include "content.h"

using namespace Blah;

bool fullscreen = false;
Screen screen = kMainMenu;

Batch *batch;
DBManager *dbManager;
User *user;

Game game;
UmStatics staticSprites;
UmButtons buttonSprites;
VcPieces pieceSprites;
VcNexuses nexusSprites;

void startup()
{
    batch = new Batch;
    Assets::load(staticSprites, buttonSprites, pieceSprites, nexusSprites, &game, screen, *user);
}

void render()
{
    App::backbuffer->clear(Color::black);

    auto scale = Vec2((float) App::width()/1280, (float) App::height()/720);
    auto transform = Mat3x2::create_transform(Vec2::zero, Vec2::zero, scale, 0);
    batch->push_matrix(transform);

    Assets::render(staticSprites, buttonSprites, pieceSprites, nexusSprites, game, screen, *user, batch);

    batch->pop_matrix();
    batch->render();
    batch->clear();
}

void update()
{
    if (Input::pressed(Key::F11)) App::fullscreen(fullscreen = !fullscreen);
    Assets::update(staticSprites, buttonSprites, pieceSprites, nexusSprites, &game, screen, *user);
}

void dispose()
{
    dbManager->updateUserData(*user);
    for (auto & staticSprite:staticSprites) delete staticSprite.second;
    for (auto & button:buttonSprites) delete button.second;
    batch->dispose();
    for (int i = 0; i < 8; i++) delete user->formationSet.forms[i];
    delete user->formationSet.forms;
    delete user;
    delete batch;
    delete dbManager;
}

int main() {
    dbManager = new DBManager((char *) "data/database.db");
    bool exit = false;
    do {
        user = Login::runSetup(*dbManager, exit);
    } while (user == nullptr && !exit);

    if (!exit) {
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
    }
    return 0;
}