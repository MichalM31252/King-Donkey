extern "C" {
#include "GameObjectFactory.h"
#include "ScreenManager.h" // temporary fix
}

GameObjectFactory::GameObjectFactory() {

}

GameObjectFactory::GameObjectFactory(GameObjectContainer* gameObjectContainer) {
	this->gameObjectContainer = gameObjectContainer;
}

void GameObjectFactory::createPlayer() {
	Player* pla = new Player();

	ScreenManager::initGameObject(pla, PLAYER_1_FILENAME);

	pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
	pla->createSrcRect();
	pla->createDestRect();

	gameObjectContainer->player = pla;
}

void GameObjectFactory::createDonkeyKong() {
	GameObject* donkeyK = new GameObject();

	ScreenManager::initGameObject(donkeyK, "./assets/DonkeyKong.bmp");

	donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	donkeyK->createSrcRect();
	donkeyK->createDestRect();

	gameObjectContainer->donkeyKong = donkeyK;
}

void GameObjectFactory::createPrincess() {
	GameObject* prin = new GameObject();

	ScreenManager::initGameObject(prin, "./assets/Princess.bmp");

	prin->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
	prin->createSrcRect();
	prin->createDestRect();

	gameObjectContainer->princess = prin;
}

void GameObjectFactory::createPlatforms1() {
	Platform* plat1 = new Platform();
	plat1->setPosition(1, 400, 400, 400);

	Platform* plat2 = new Platform();
	plat2->setPosition(400, 400, 500, 300);

	Platform* plat3 = new Platform();
	plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300);

	Platform* plat4 = new Platform();
	plat4->setPosition(1, 130, 570, 130);

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

	PlatformHolder* pH = new PlatformHolder();
	initPlatformHolder(pH);
	addPlatform(pH, plat1);
	addPlatform(pH, plat2);
	addPlatform(pH, plat3);
	addPlatform(pH, plat4);
	addPlatform(pH, plat5);

	gameObjectContainer->platformHolder = pH;
}

void GameObjectFactory::createLadders1() {
	GameObject* ladd1 = new GameObject();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(525, 129);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

	GameObject* ladd2 = new GameObject();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(250, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 50);
	ladd2->setDestRect(LADDER_WIDTH, 50);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);
	gameObjectContainer->ladderHolder = laddH;
}

void GameObjectFactory::createBarrels() {
	// std::unique_ptr<BarrelHolder> barrelHolder
	std::unique_ptr<MovableGameObject> barrel1 = std::make_unique<MovableGameObject>();

	ScreenManager::initGameObject(barrel1, BARREL_1_FILENAME);

	barrel1->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel1->createSrcRect();
	barrel1->createDestRect();
	barrel1->objectSpeed = DEFAULT_BARREL_SPEED;

	BarrelHolder* barrelH = new BarrelHolder();
	initBarrelHolder(barrelH);
	addBarrel(barrelH, barrel1);

	gameObjectContainer->barrelFactory = new BarrelFactory();
	gameObjectContainer->barrelFactory->barrelHolder = barrelH;
	gameObjectContainer->barrelFactory->setPosition(gameObjectContainer->donkeyKong->xpos + gameObjectContainer->donkeyKong->destRect.w + +SMALL_MARGIN, gameObjectContainer->donkeyKong->ypos);
}

void GameObjectFactory::createPlatforms2() {
	Platform* plat1 = new Platform();
	plat1->setPosition(TINY_MARGIN, 400, SCREEN_WIDTH - 1, 400);

	Platform* plat2 = new Platform();
	plat2->setPosition(130, 130, 300, 300);

	Platform* plat3 = new Platform();
	plat3->setPosition(TINY_MARGIN, 130, 130, 130);

	Platform* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, 130, 130);

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 80);

	Platform* plat6 = new Platform();
	plat6->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - LARGE_MARGIN, 230);

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);
	addPlatform(platH, plat6);

	gameObjectContainer->platformHolder = platH;
}

void GameObjectFactory::createLadders2() {
	GameObject* ladd1 = new GameObject();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

	GameObject* ladd2 = new GameObject();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 150);
	ladd2->setDestRect(LADDER_WIDTH, 150);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);

	gameObjectContainer->ladderHolder = laddH;
}

void GameObjectFactory::createPlatforms3() {
	Platform* plat1 = new Platform();
	plat1->setPosition(STARTING_X, 400, SCREEN_WIDTH - TINY_MARGIN, 400);

	Platform* plat2 = new Platform();
	plat2->setPosition(LARGE_MARGIN, 300, SCREEN_WIDTH - LARGE_MARGIN, 300);

	Platform* plat3 = new Platform();
	plat3->setPosition(LARGE_MARGIN, 200, SCREEN_WIDTH - LARGE_MARGIN, 200);

	Platform* plat4 = new Platform();
	plat4->setPosition(TINY_MARGIN, 130, SCREEN_WIDTH - LARGE_MARGIN, 130);

	Platform* plat5 = new Platform();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

	PlatformHolder* platH = new PlatformHolder();
	initPlatformHolder(platH);
	addPlatform(platH, plat1);
	addPlatform(platH, plat2);
	addPlatform(platH, plat3);
	addPlatform(platH, plat4);
	addPlatform(platH, plat5);

	gameObjectContainer->platformHolder = platH;
}

void GameObjectFactory::createLadders3() {
	GameObject* ladd1 = new GameObject();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	GameObject* ladd2 = new GameObject();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(LARGE_MARGIN, 199);
	ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	GameObject* ladd3 = new GameObject();

	ScreenManager::initGameObject(ladd3, "./assets/Ladder.bmp");

	ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
	ladd3->setSrcRect(LADDER_WIDTH, 70);
	ladd3->setDestRect(LADDER_WIDTH, 70);

	GameObject* ladd4 = new GameObject();

	ScreenManager::initGameObject(ladd4, "./assets/Ladder.bmp");

	ladd4->setPosition(250, 79);
	ladd4->setSrcRect(LADDER_WIDTH, 50);
	ladd4->setDestRect(LADDER_WIDTH, 50);

	LadderHolder* laddH = new LadderHolder();
	initLadderHolder(laddH);
	addLadder(laddH, ladd1);
	addLadder(laddH, ladd2);
	addLadder(laddH, ladd3);
	addLadder(laddH, ladd4);
	gameObjectContainer->ladderHolder = laddH;
}

void GameObjectFactory::createBoard(int boardId) {
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
	createBarrels();
}

GameObjectFactory::~GameObjectFactory() {

}