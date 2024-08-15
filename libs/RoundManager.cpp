#include "RoundManager.h"

RoundManager::RoundManager() {
    screenManager = std::make_unique<ScreenManager>();
    gameObjectFactory = std::make_unique<GameObjectFactory>();
    gameObjectContainer = std::make_unique<GameObjectContainer>();
    collisionResolver = std::make_unique<CollisionResolver>(gameObjectContainer.get(), screenManager.get());
}

RoundManager::RoundManager(std::unique_ptr<ScreenManager> screenManager,
    std::unique_ptr<GameObjectFactory> gameObjectFactory,
    std::unique_ptr<GameObjectContainer> gameObjectContainer,
    std::unique_ptr<CollisionResolver> collisionResolver)
    : screenManager(std::move(screenManager)),
    gameObjectFactory(std::move(gameObjectFactory)),
    gameObjectContainer(std::move(gameObjectContainer)),
    collisionResolver(std::move(collisionResolver))
{
}

void RoundManager::handleCurrentRound(KeyboardManager& eventHandler, int* startAnotherRound) {
    bool quit = false;
    while (!quit) {
        screenManager->handleDifferentComputers();
        screenManager->updateWorldTime();
        screenManager->handleFPSTimer();
        screenManager->drawOutlineOfTheBoard();
        screenManager->drawAdditionalInfo();
        screenManager->drawElements();
        screenManager->serveNextFrame();
        screenManager->frames++;

        eventHandler.handleEvents(quit, screenManager->deltaTime, gameObjectContainer->player, *startAnotherRound);

        gameObjectContainer->player->update(screenManager->deltaTime);

        collisionResolver->handlePlayerCollision();

        // screenManager->handlePlayerSprite(gameObjectContainer->player);

        gameObjectContainer->barrelFactory->update(screenManager->deltaTime);

		gameObjectContainer->barrelFactory->barrelHolder->updateBarrels(screenManager->deltaTime);

        collisionResolver->handleBarrelsCollision(&quit, startAnotherRound);
    };
}

void RoundManager::handleRound(int startAnotherRound) {
    KeyboardManager eventHandler;
    screenManager->createFramerate();

    decideWhichBoardToCreate(startAnotherRound);
    handleCurrentRound(eventHandler, &startAnotherRound);

    if (startAnotherRound) {
        handleRound(startAnotherRound);
    }
}

void RoundManager::decideWhichBoardToCreate(int startAnotherRound) {
    if (startAnotherRound) {
        if (startAnotherRound == BOARD_ID_A) {
            gameObjectFactory->createBoard(BOARD_ID_A);
        }
        if (startAnotherRound == BOARD_ID_B) {
            gameObjectFactory->createBoard(BOARD_ID_B);
        }
        if (startAnotherRound == BOARD_ID_C) {
            gameObjectFactory->createBoard(BOARD_ID_C);
        }
    }
    else {
        gameObjectFactory->createBoard(BOARD_ID_A);
    }
}
