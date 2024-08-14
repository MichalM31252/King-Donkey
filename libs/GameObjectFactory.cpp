extern "C" {
#include "GameObjectFactory.h"
#include "ScreenManager.h" // temporary fix
}

GameObjectFactory::GameObjectFactory() {

}

GameObjectFactory::GameObjectFactory(std::unique_ptr<GameObjectContainer>& gameObjectContainer) {
	this->gameObjectContainer = std::move(gameObjectContainer);
}

void GameObjectFactory::createPlayer() {
	std::unique_ptr<Player> pla = std::make_unique<Player>();

	ScreenManager::initGameObject(pla, PLAYER_1_FILENAME);

	pla->setPosition(STARTING_X_PLAYER, STARTING_Y_PLAYER);
	pla->createSrcRect();
	pla->createDestRect();

	gameObjectContainer->player = std::move(pla);
}

void GameObjectFactory::createDonkeyKong() {
	std::unique_ptr<GameObject> donkeyK = std::make_unique<GameObject>();

	ScreenManager::initGameObject(donkeyK, "./assets/DonkeyKong.bmp");

	donkeyK->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	donkeyK->createSrcRect();
	donkeyK->createDestRect();

	gameObjectContainer->donkeyKong = std::move(donkeyK);
}

void GameObjectFactory::createPrincess() {
	std::unique_ptr<GameObject> prin = std::make_unique<GameObject>();

	ScreenManager::initGameObject(prin, "./assets/Princess.bmp");

	prin->setPosition(STARTING_X_PRINCESS, STARTING_Y_PRINCESS);
	prin->createSrcRect();
	prin->createDestRect();

	gameObjectContainer->princess = std::move(prin);
}

void GameObjectFactory::createPlatforms1() {
	std::unique_ptr<Platform> plat1 = std::make_unique<Platform>();
	plat1->setPosition(1, 400, 400, 400);

	std::unique_ptr<Platform> plat2 = std::make_unique<Platform>();
	plat2->setPosition(400, 400, 500, 300);

	std::unique_ptr<Platform> plat3 = std::make_unique<Platform>();
	plat3->setPosition(500, 300, SCREEN_WIDTH - 1, 300);

	std::unique_ptr<Platform> plat4 = std::make_unique<Platform>();
	plat4->setPosition(1, 130, 570, 130);

	std::unique_ptr<Platform> plat5 = std::make_unique<Platform>();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

	std::unique_ptr<PlatformHolder> platH = std::make_unique<PlatformHolder>();
	platH->addPlatform(std::move(plat1));
	platH->addPlatform(std::move(plat2));
	platH->addPlatform(std::move(plat3));
	platH->addPlatform(std::move(plat4));
	platH->addPlatform(std::move(plat5));

	gameObjectContainer->platformHolder = std::move(platH);
}

void GameObjectFactory::createLadders1() {
	std::unique_ptr<GameObject> ladd1 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(525, 129);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

	// GameObject* ladd2 = new GameObject();
	std::unique_ptr<GameObject> ladd2 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(250, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 50);
	ladd2->setDestRect(LADDER_WIDTH, 50);

	// LadderHolder* laddH = new LadderHolder();
	std::unique_ptr<LadderHolder> laddH = std::make_unique<LadderHolder>();
	laddH->addLadder(std::move(ladd1));
	laddH->addLadder(std::move(ladd2));
	gameObjectContainer->ladderHolder = std::move(laddH);
}

void GameObjectFactory::createBarrels() { // work on this 
	std::unique_ptr<MovableGameObject> barrel1 = std::make_unique<MovableGameObject>();

	ScreenManager::initGameObject(barrel1, BARREL_1_FILENAME);

	barrel1->setPosition(STARTING_X_DONKEY_KONG, STARTING_Y_DONKEY_KONG);
	barrel1->createSrcRect();
	barrel1->createDestRect();
	barrel1->objectSpeed = DEFAULT_BARREL_SPEED;

	std::unique_ptr<BarrelHolder> barrelH = std::make_unique<BarrelHolder>();
	initBarrelHolder(barrelH);
	addBarrel(barrelH, barrel1);

	gameObjectContainer->barrelFactory = new BarrelFactory();
	gameObjectContainer->barrelFactory->barrelHolder = barrelH;
	gameObjectContainer->barrelFactory->setPosition(gameObjectContainer->donkeyKong->xpos + gameObjectContainer->donkeyKong->destRect.w + +SMALL_MARGIN, gameObjectContainer->donkeyKong->ypos);
}

void GameObjectFactory::createPlatforms2() {
	std::unique_ptr<Platform> plat1 = std::make_unique<Platform>();
	plat1->setPosition(TINY_MARGIN, 400, SCREEN_WIDTH - 1, 400);

	std::unique_ptr<Platform> plat2 = std::make_unique<Platform>();
	plat2->setPosition(130, 130, 300, 300);

	std::unique_ptr<Platform> plat3 = std::make_unique<Platform>();
	plat3->setPosition(TINY_MARGIN, 130, 130, 130);

	std::unique_ptr<Platform> plat4 = std::make_unique<Platform>();
	plat4->setPosition(TINY_MARGIN, 130, 130, 130);

	std::unique_ptr<Platform> plat5 = std::make_unique<Platform>();
	plat5->setPosition(200, 80, SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 80);

	std::unique_ptr<Platform> plat6 = std::make_unique<Platform>();
	plat6->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 230, SCREEN_WIDTH - LARGE_MARGIN, 230);

	std::unique_ptr<PlatformHolder> platH = std::make_unique<PlatformHolder>();
	platH->addPlatform(std::move(plat1));
	platH->addPlatform(std::move(plat2));
	platH->addPlatform(std::move(plat3));
	platH->addPlatform(std::move(plat4));
	platH->addPlatform(std::move(plat5));
	platH->addPlatform(std::move(plat6));

	gameObjectContainer->platformHolder = std::move(platH);
}

void GameObjectFactory::createLadders2() {
	std::unique_ptr<GameObject> ladd1 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 229);
	ladd1->setSrcRect(LADDER_WIDTH, 170);
	ladd1->setDestRect(LADDER_WIDTH, 170);

	std::unique_ptr<GameObject> ladd2 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH - LADDER_WIDTH, 79);
	ladd2->setSrcRect(LADDER_WIDTH, 150);
	ladd2->setDestRect(LADDER_WIDTH, 150);

	std::unique_ptr<LadderHolder> laddH = std::make_unique<LadderHolder>();
	laddH->addLadder(std::move(ladd1));
	laddH->addLadder(std::move(ladd2));

	gameObjectContainer->ladderHolder = std::move(laddH);
}

void GameObjectFactory::createPlatforms3() {
	std::unique_ptr<Platform> plat1 = std::make_unique<Platform>();
	plat1->setPosition(STARTING_X, 400, SCREEN_WIDTH - TINY_MARGIN, 400);

	std::unique_ptr<Platform> plat2 = std::make_unique<Platform>();
	plat2->setPosition(LARGE_MARGIN, 300, SCREEN_WIDTH - LARGE_MARGIN, 300);

	std::unique_ptr<Platform> plat3 = std::make_unique<Platform>();
	plat3->setPosition(LARGE_MARGIN, 200, SCREEN_WIDTH - LARGE_MARGIN, 200);

	std::unique_ptr<Platform> plat4 = std::make_unique<Platform>();
	plat4->setPosition(TINY_MARGIN, 130, SCREEN_WIDTH - LARGE_MARGIN, 130);

	std::unique_ptr<Platform> plat5 = std::make_unique<Platform>();
	plat5->setPosition(200, 80, 250 + LADDER_WIDTH, 80);

	std::unique_ptr<PlatformHolder> platH = std::make_unique<PlatformHolder>();
	platH->addPlatform(std::move(plat1));
	platH->addPlatform(std::move(plat2));
	platH->addPlatform(std::move(plat3));
	platH->addPlatform(std::move(plat4));
	platH->addPlatform(std::move(plat5));

	gameObjectContainer->platformHolder = std::move(platH);
}

void GameObjectFactory::createLadders3() {
	std::unique_ptr<GameObject> ladd1 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd1, "./assets/Ladder.bmp");

	ladd1->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 299);
	ladd1->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd1->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	std::unique_ptr<GameObject> ladd2 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd2, "./assets/Ladder.bmp");

	ladd2->setPosition(LARGE_MARGIN, 199);
	ladd2->setSrcRect(LADDER_WIDTH, LARGE_MARGIN);
	ladd2->setDestRect(LADDER_WIDTH, LARGE_MARGIN);

	std::unique_ptr<GameObject> ladd3 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd3, "./assets/Ladder.bmp");

	ladd3->setPosition(SCREEN_WIDTH - LARGE_MARGIN - LADDER_WIDTH, 129);
	ladd3->setSrcRect(LADDER_WIDTH, 70);
	ladd3->setDestRect(LADDER_WIDTH, 70);

	std::unique_ptr<GameObject> ladd4 = std::make_unique<GameObject>();

	ScreenManager::initGameObject(ladd4, "./assets/Ladder.bmp");

	ladd4->setPosition(250, 79);
	ladd4->setSrcRect(LADDER_WIDTH, 50);
	ladd4->setDestRect(LADDER_WIDTH, 50);

	std::unique_ptr<LadderHolder> laddH = std::make_unique<LadderHolder>();
	laddH->addLadder(std::move(ladd1));
	laddH->addLadder(std::move(ladd2));
	laddH->addLadder(std::move(ladd3));
	laddH->addLadder(std::move(ladd4));
	gameObjectContainer->ladderHolder = std::move(laddH);
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