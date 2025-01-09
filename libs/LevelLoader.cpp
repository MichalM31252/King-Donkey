#include "LevelLoader.h"
#include "ScreenManager.h"

LevelLoader::LevelLoader(std::shared_ptr<GameObjectContainer> container)
    : gameObjectContainer(container)
{
}

void LevelLoader::createPlayer() {
    auto player = std::make_shared<Player>();
    ScreenManager::setSurface(player.get(), PLAYER_1_FILENAME);

    player->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
    player->createSrcRect();
    player->createDestRect();

    gameObjectContainer->player = player;
}

void LevelLoader::createDonkeyKong() {
    gameObjectContainer->barrelContainer = std::make_shared<BarrelContainer>();

    auto donkeyKong = std::make_shared<Gorilla>(gameObjectContainer->barrelContainer);
    ScreenManager::setSurface(donkeyKong.get(), DONKEY_KONG_FILENAME);

    donkeyKong->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
    donkeyKong->createSrcRect();
    donkeyKong->createDestRect();

    gameObjectContainer->donkeyKong = donkeyKong;
}

void LevelLoader::createPrincess() {
    auto princess = std::make_shared<GameObject>();
    ScreenManager::setSurface(princess.get(), PRINCESS_FILENAME);

    princess->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
    princess->createSrcRect();
    princess->createDestRect();

    gameObjectContainer->princess = princess;
}

// Creates platforms for level 1
void LevelLoader::createPlatforms1() {
    auto platformContainer = std::make_shared<PlatformContainer>();

    auto plat1 = std::make_shared<Platform>(1, 400, 400, 8, 0);
	ScreenManager::setSurface(plat1.get(), PLATFORM_FILENAME);
    platformContainer->addPlatform(plat1);

	// Platform 2: Tilted 
	auto plat2 = std::make_shared<Platform>(400 - 20, 400 - 50, 141, 8, 135);
	ScreenManager::setSurface(plat2.get(), PLATFORM_FILENAME);
	platformContainer->addPlatform(plat2);

	auto plat3 = std::make_shared<Platform>(500, 300, SCREEN_WIDTH - 1 - 500, 8, 0);
	ScreenManager::setSurface(plat3.get(), PLATFORM_FILENAME);
	platformContainer->addPlatform(plat3);

	auto plat4 = std::make_shared<Platform>(1, 130, 570, 8, 0);
	ScreenManager::setSurface(plat4.get(), PLATFORM_FILENAME);
	platformContainer->addPlatform(plat4);

	auto plat5 = std::make_shared<Platform>(200, 80, 50 + LADDER_WIDTH, 8, 0);
	ScreenManager::setSurface(plat5.get(), PLATFORM_FILENAME);
	platformContainer->addPlatform(plat5);

    gameObjectContainer->platformContainer = platformContainer;
}

void LevelLoader::createLadders1() {
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(525, 129);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(250, 79);
    ladd2->setSrcRect(LADDER_WIDTH, 50);
    ladd2->setDestRect(LADDER_WIDTH, 50);

    auto ladderContainer = std::make_shared<LadderContainer>();
    ladderContainer->addLadder(ladd1);
    ladderContainer->addLadder(ladd2);
    gameObjectContainer->ladderContainer = ladderContainer;
}
void LevelLoader::createLadders2() {
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
    ladd2->setSrcRect(LADDER_WIDTH, 150);
    ladd2->setDestRect(LADDER_WIDTH, 150);

    auto laddH = std::make_shared<LadderContainer>();
    laddH->addLadder(ladd1);
    laddH->addLadder(ladd2);
    gameObjectContainer->ladderContainer = laddH;
}


void LevelLoader::createLadders3() {
    auto ladd1 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd1.get(), LADDER_FILENAME);
    ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
    ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
    ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto ladd2 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd2.get(), LADDER_FILENAME);
    ladd2->setPosition(LARGE_MARGIN, 199);
    ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
    ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto ladd3 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd3.get(), LADDER_FILENAME);
    ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
    ladd3->setSrcRect(LADDER_WIDTH, 70);
    ladd3->setDestRect(LADDER_WIDTH, 70);

    auto ladd4 = std::make_shared<GameObject>();
    ScreenManager::setSurface(ladd4.get(), LADDER_FILENAME);
    ladd4->setPosition(250, 79);
    ladd4->setSrcRect(LADDER_WIDTH, 50);
    ladd4->setDestRect(LADDER_WIDTH, 50);

    auto laddH = std::make_shared<LadderContainer>();
    laddH->addLadder(ladd1);
    laddH->addLadder(ladd2);
    laddH->addLadder(ladd3);
    laddH->addLadder(ladd4);

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
