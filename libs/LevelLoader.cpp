#include "LevelLoader.h"
#include "ScreenManager.h"

LevelLoader::LevelLoader(GameObjectContainer* gameObjectContainer)
    : gameObjectContainer(gameObjectContainer)
{
}

void LevelLoader::createPlayer() {
    auto* pla = new Player();

	ScreenManager::loadTexture(pla, PLAYER_1_FILENAME);

    pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
    pla->createSrcRect();
    pla->createDestRect();

    gameObjectContainer->player = pla;
}

void LevelLoader::createDonkeyKong() {
    gameObjectContainer->barrelContainer = new BarrelContainer();

    auto* donkeyK = new Gorilla(gameObjectContainer->barrelContainer);

	ScreenManager::loadTexture(donkeyK, DONKEY_KONG_FILENAME);

    donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
    donkeyK->createSrcRect();
    donkeyK->createDestRect();

    gameObjectContainer->donkeyKong = donkeyK;

	// this is not the place where you decide where the barrels are thrown
	// this doesnt really do anything
    donkeyK->barrelFactory->setPosition(0, 0); 
}

void LevelLoader::createPrincess() {
    auto* prin = new GameObject();

	ScreenManager::loadTexture(prin, PRINCESS_FILENAME);

    prin->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
    prin->createSrcRect();
    prin->createDestRect();

    gameObjectContainer->princess = prin;
}

void LevelLoader::createPlatforms1() {
    auto* plat1 = new Platform();
    plat1->setPosition(1, 400, 400, 400);

    auto* plat2 = new Platform();
    plat2->setPosition(400, 400, 500, 300);

    auto* plat3 = new Platform();
    plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300);

    auto* plat4 = new Platform();
    plat4->setPosition(1, 130, 570, 130);

    auto* plat5 = new Platform();
    plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

    auto* platH = new PlatformContainer();
    platH->addPlatform(plat1);
    platH->addPlatform(plat2);
    platH->addPlatform(plat3);
    platH->addPlatform(plat4);
    platH->addPlatform(plat5);

    gameObjectContainer->platformContainer = platH;
}

void LevelLoader::createLadders1() {
    auto* ladd1 = new GameObject();

	ScreenManager::loadTexture(ladd1, LADDER_FILENAME);

    ladd1->setPosition(525, 129);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto* ladd2 = new GameObject();

	ScreenManager::loadTexture(ladd2, LADDER_FILENAME);

    ladd2->setPosition(250, 79);
    ladd2->setSrcRect(LADDER_WIDTH, 50);
    ladd2->setDestRect(LADDER_WIDTH, 50);

    auto* laddH = new LadderContainer();
    laddH->addLadder(ladd1);
    laddH->addLadder(ladd2);
    gameObjectContainer->ladderContainer = laddH;
}

void LevelLoader::createPlatforms2() {
    auto* plat1 = new Platform();
	plat1->setPosition(TINY_MARGIN, 400, SCREEN_WIDTH - 1, 400);

    auto* plat2 = new Platform();
	plat2->setPosition(130, 130, 300, 300);

    auto* plat3 = new Platform();
	plat3->setPosition(TINY_MARGIN, 130, 130, 130);

    auto* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, 130, 130);

    auto* plat5 = new Platform();
	plat5->setPosition(200, 80, SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 80);

    auto* plat6 = new Platform();
	plat6->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - LARGE_MARGIN, 230);

    auto* platH = new PlatformContainer();
	platH->addPlatform(plat1);
	platH->addPlatform(plat2);
	platH->addPlatform(plat3);
	platH->addPlatform(plat4);
	platH->addPlatform(plat5);
	platH->addPlatform(plat6);

	gameObjectContainer->platformContainer = platH;
}

void LevelLoader::createLadders2() {
    auto* ladd1 = new GameObject();

	ScreenManager::loadTexture(ladd1, LADDER_FILENAME);

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

    auto* ladd2 = new GameObject();

	ScreenManager::loadTexture(ladd2, LADDER_FILENAME);

	ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 150);
	ladd2->setDestRect(LADDER_WIDTH, 150);

    auto* laddH = new LadderContainer();
	laddH->addLadder(ladd1);
	laddH->addLadder(ladd2);

	gameObjectContainer->ladderContainer = laddH;
}

void LevelLoader::createPlatforms3() {
    auto* plat1 = new Platform();
	plat1->setPosition(STARTING_X, 400, SCREEN_WIDTH - TINY_MARGIN, 400);

    auto* plat2 = new Platform();
	plat2->setPosition(LARGE_MARGIN, 300, SCREEN_WIDTH - LARGE_MARGIN, 300);

    auto* plat3 = new Platform();
	plat3->setPosition(LARGE_MARGIN, 200, SCREEN_WIDTH - LARGE_MARGIN, 200);

    auto* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, SCREEN_WIDTH - LARGE_MARGIN, 130);

    auto* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

    auto* platH = new PlatformContainer();
	platH->addPlatform(plat1);
	platH->addPlatform(plat2);
	platH->addPlatform(plat3);
	platH->addPlatform(plat4);
	platH->addPlatform(plat5);

	gameObjectContainer->platformContainer = platH;
}

void LevelLoader::createLadders3() {
    auto* ladd1 = new GameObject();

	ScreenManager::loadTexture(ladd1, LADDER_FILENAME);

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto* ladd2 = new GameObject();

	ScreenManager::loadTexture(ladd2, LADDER_FILENAME);

	ladd2->setPosition(LARGE_MARGIN, 199);
	ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto* ladd3 = new GameObject();

	ScreenManager::loadTexture(ladd3, LADDER_FILENAME);

	ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
	ladd3->setSrcRect(LADDER_WIDTH, 70);
	ladd3->setDestRect(LADDER_WIDTH, 70);

    auto* ladd4 = new GameObject();

	ScreenManager::loadTexture(ladd4, LADDER_FILENAME);

	ladd4->setPosition(250, 79);
	ladd4->setSrcRect(LADDER_WIDTH, 50);
	ladd4->setDestRect(LADDER_WIDTH, 50);

    auto* laddH = new LadderContainer();
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
    createPlatforms2();
    createLadders2();
}

void LevelLoader::loadLevel3() {
    createPlayer();
    createDonkeyKong();
    createPrincess();
    createPlatforms3();
    createLadders3();
}
