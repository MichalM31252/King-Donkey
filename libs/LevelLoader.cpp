#include "LevelLoader.h"
#include "ScreenManager.h"

LevelLoader::LevelLoader(GameObjectContainer* gameObjectContainer)
    : gameObjectContainer(gameObjectContainer)
{
}

void LevelLoader::createPlayer() {
    auto* pla = new Player();

    ScreenManager::initGameObject(pla, PLAYER_1_FILENAME);

    pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
    pla->createSrcRect();
    pla->createDestRect();

    gameObjectContainer->player = pla;
}

void LevelLoader::createDonkeyKong() {
    gameObjectContainer->barrelContainer = new BarrelContainer();

    auto* donkeyK = new Gorilla(gameObjectContainer->barrelContainer);

    ScreenManager::initGameObject(donkeyK, "./assets/DonkeyKong.bmp");

    donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
    donkeyK->createSrcRect();
    donkeyK->createDestRect();

    gameObjectContainer->donkeyKong = donkeyK;

    donkeyK->barrelFactory->setPosition(gameObjectContainer->donkeyKong->xpos + gameObjectContainer->donkeyKong->destRect.w + SMALL_MARGIN, gameObjectContainer->donkeyKong->ypos);
}

void LevelLoader::createPrincess() {
    auto* prin = new GameObject();

    ScreenManager::initGameObject(prin, "./assets/Princess.bmp");

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

    ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

    ladd1->setPosition(525, 129);
    ladd1->setSrcRect(LADDER_WIDTH, 170);
    ladd1->setDestRect(LADDER_WIDTH, 170);

    auto* ladd2 = new GameObject();

    ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

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

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

    auto* ladd2 = new GameObject();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

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

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto* ladd2 = new GameObject();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(LARGE_MARGIN, 199);
	ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

    auto* ladd3 = new GameObject();

	ScreenManager::initGameObject(ladd3, "./assets/Ladder.bmp");

	ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
	ladd3->setSrcRect(LADDER_WIDTH, 70);
	ladd3->setDestRect(LADDER_WIDTH, 70);

    auto* ladd4 = new GameObject();

	ScreenManager::initGameObject(ladd4, "./assets/Ladder.bmp");

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

void LevelLoader::createBoard(int boardId) {
    createPlayer();
    createDonkeyKong();
    createPrincess();
    if (boardId == 1) {
        createPlatforms1();
        createLadders1();
    }
    if (boardId == 2) {
        createPlatforms2();
        createLadders2();
    }
    if (boardId == 3) {
        createPlatforms3();
        createLadders3();
    }
}

void LevelLoader::decideWhichBoardToCreate(int startAnotherRound) {
    if (startAnotherRound) {
        if (startAnotherRound == BOARD_ID_A) {
            createBoard(BOARD_ID_A);
        }
        if (startAnotherRound == BOARD_ID_B) {
            createBoard(BOARD_ID_B);
        }
        if (startAnotherRound == BOARD_ID_C) {
            createBoard(BOARD_ID_C);
        }
    }
    else {
        createBoard(BOARD_ID_A);
    }
}