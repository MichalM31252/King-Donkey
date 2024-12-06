#include "LevelLoader.h"
#include "ScreenManager.h"

LevelLoader::LevelLoader(std::shared_ptr<GameObjectContainer> container)
    : gameObjectContainer(container)
{
}

void LevelLoader::createPlayer() {
    auto player = std::make_shared<Player>();
    ScreenManager::loadTexture(player.get(), PLAYER_1_FILENAME);

    player->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
    player->createSrcRect();
    player->createDestRect();

    gameObjectContainer->player = player;
}

void LevelLoader::createDonkeyKong() {
    gameObjectContainer->barrelContainer = std::make_shared<BarrelContainer>();

    auto donkeyKong = std::make_shared<Gorilla>(gameObjectContainer->barrelContainer);
    ScreenManager::loadTexture(donkeyKong.get(), DONKEY_KONG_FILENAME);

    donkeyKong->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
    donkeyKong->createSrcRect();
    donkeyKong->createDestRect();

    gameObjectContainer->donkeyKong = donkeyKong;
}

void LevelLoader::createPrincess() {
    auto princess = std::make_shared<GameObject>();
    ScreenManager::loadTexture(princess.get(), PRINCESS_FILENAME);

    princess->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
    princess->createSrcRect();
    princess->createDestRect();

    gameObjectContainer->princess = princess;
}

//void LevelLoader::createPlatforms1() {
//    auto plat1 = std::make_shared<Platform>();
//    plat1->setPosition(1, 400, 400, 400);
//
//    auto plat2 = std::make_shared<Platform>();
//    plat2->setPosition(400, 400, 500, 300);
//
//    auto plat3 = std::make_shared<Platform>();
//    plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300);
//
//    auto plat4 = std::make_shared<Platform>();
//    plat4->setPosition(1, 130, 570, 130);
//
//    auto plat5 = std::make_shared<Platform>();
//    plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);
//
//    auto platformContainer = std::make_shared<PlatformContainer>();
//    platformContainer->addPlatform(plat1);
//    platformContainer->addPlatform(plat2);
//    platformContainer->addPlatform(plat3);
//    platformContainer->addPlatform(plat4);
//    platformContainer->addPlatform(plat5);
//
//    gameObjectContainer->platformContainer = platformContainer;
//}

// Creates platforms for level 1
void LevelLoader::createPlatforms1() {
    auto platformContainer = std::make_shared<PlatformContainer>();

    // Platform 1: Horizontal
    auto plat1 = std::make_shared<Platform>(400, 400, 300, 20, 0.0); // x, y, width, height, angle
    platformContainer->addPlatform(plat1);

    // Platform 2: Tilted
    auto plat2 = std::make_shared<Platform>(400, 400, 200, 20, -15.0); // tilted at -15 degrees
    platformContainer->addPlatform(plat2);

    // Platform 3: Horizontal
    auto plat3 = std::make_shared<Platform>(600, 300, 300, 20, 0.0);
    platformContainer->addPlatform(plat3);

    // Platform 4: Tilted
    auto plat4 = std::make_shared<Platform>(1, 130, 570, 20, 10.0); // tilted at 10 degrees
    platformContainer->addPlatform(plat4);

    gameObjectContainer->platformContainer = platformContainer;
}

void LevelLoader::createLadders1() {
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(525, 129);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(250, 79);
    ladd2->setSrcRect(LADDER_WIDTH, 50);
    ladd2->setDestRect(LADDER_WIDTH, 50);

    auto ladderContainer = std::make_shared<LadderContainer>();
    ladderContainer->addLadder(ladd1);
    ladderContainer->addLadder(ladd2);
    gameObjectContainer->ladderContainer = ladderContainer;
}

//void LevelLoader::createPlatforms2() {
//    auto plat1 = std::make_shared<Platform>();
//    plat1->setPosition(TINY_MARGIN, 400, SCREEN_WIDTH - 1, 400);
//
//    auto plat2 = std::make_shared<Platform>();
//    plat2->setPosition(130, 130, 300, 300);
//
//    auto plat3 = std::make_shared<Platform>();
//    plat3->setPosition(TINY_MARGIN, 130, 130, 130);
//
//    auto plat4 = std::make_shared<Platform>();
//    plat4->setPosition(TINY_MARGIN, 130, 130, 130);
//
//    auto plat5 = std::make_shared<Platform>();
//    plat5->setPosition(200, 80, SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 80);
//
//    auto plat6 = std::make_shared<Platform>();
//    plat6->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - LARGE_MARGIN, 230);
//
//    auto platformContainer = std::make_shared<PlatformContainer>();
//    platformContainer->addPlatform(plat1);
//    platformContainer->addPlatform(plat2);
//    platformContainer->addPlatform(plat3);
//    platformContainer->addPlatform(plat4);
//    platformContainer->addPlatform(plat5);
//    platformContainer->addPlatform(plat6);
//
//    gameObjectContainer->platformContainer = platformContainer;
//}

void LevelLoader::createLadders2() {
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
    ladd2->setSrcRect(LADDER_WIDTH, 150);
    ladd2->setDestRect(LADDER_WIDTH, 150);

    auto laddH = std::make_shared<LadderContainer>();
    laddH->addLadder(ladd1);
    laddH->addLadder(ladd2);
    gameObjectContainer->ladderContainer = laddH;
}

//void LevelLoader::createPlatforms3() {
//    auto plat1 = std::make_shared<Platform>();
//    plat1->setPosition(STARTING_X, 400, SCREEN_WIDTH - TINY_MARGIN, 400);
//
//    auto plat2 = std::make_shared<Platform>();
//    plat2->setPosition(LARGE_MARGIN, 300, SCREEN_WIDTH - LARGE_MARGIN, 300);
//
//    auto plat3 = std::make_shared<Platform>();
//    plat3->setPosition(LARGE_MARGIN, 200, SCREEN_WIDTH - LARGE_MARGIN, 200);
//
//    auto plat4 = std::make_shared<Platform>();
//    plat4->setPosition(TINY_MARGIN, 130, SCREEN_WIDTH - LARGE_MARGIN, 130);
//
//    auto plat5 = std::make_shared<Platform>();
//    plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);
//
//    auto platH = std::make_shared<PlatformContainer>();
//    platH->addPlatform(plat1);
//    platH->addPlatform(plat2);
//    platH->addPlatform(plat3);
//    platH->addPlatform(plat4);
//    platH->addPlatform(plat5);
//
//    gameObjectContainer->platformContainer = platH;
//}

void LevelLoader::createLadders3() {
    // Creating each ladder with a shared pointer
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
    ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
    ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(LARGE_MARGIN, 199);
    ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
    ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto ladd3 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd3.get(), LADDER_FILENAME);
    ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
    ladd3->setSrcRect(LADDER_WIDTH, 70);
    ladd3->setDestRect(LADDER_WIDTH, 70);

    auto ladd4 = std::make_shared<GameObject>();
    ScreenManager::loadTexture(ladd4.get(), LADDER_FILENAME);
    ladd4->setPosition(250, 79);
    ladd4->setSrcRect(LADDER_WIDTH, 50);
    ladd4->setDestRect(LADDER_WIDTH, 50);

    // Creating the LadderContainer with a shared pointer
    auto laddH = std::make_shared<LadderContainer>();
    laddH->addLadder(ladd1);
    laddH->addLadder(ladd2);
    laddH->addLadder(ladd3);
    laddH->addLadder(ladd4);

    // Assigning the shared ladder container to gameObjectContainer
    gameObjectContainer->ladderContainer = laddH;
}

void LevelLoader::loadLevel1() {
    createPlayer();
    createDonkeyKong();
    createPrincess();
    createPlatforms1();
    createLadders1();
}

void LevelLoader::loadLevel2() {
    createPlayer();
    createDonkeyKong();
    createPrincess();
    //createPlatforms2();
    createLadders2();
}

void LevelLoader::loadLevel3() {
    createPlayer();
    createDonkeyKong();
    createPrincess();
    //createPlatforms3();
    createLadders3();
}
