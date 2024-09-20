#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(std::make_unique<ScreenManager>(gameObjectContainer.get()))
	, levelLoader(std::make_unique<LevelLoader>(gameObjectContainer.get()))
	, keyboardManager(std::make_unique<KeyboardManager>())
	, collisionResolver(std::make_unique<CollisionResolver>(gameObjectContainer.get(), screenManager.get()))
	, collisionDetector(std::make_unique<CollisionDetector>())
	, physicsManager(std::make_unique<PhysicsManager>())
{
}

void Game::initGame() const {
    screenManager->createSDL();
    screenManager->createFramerate();
	int startAnotherRound = 0;
     
    levelLoader->decideWhichBoardToCreate(startAnotherRound); // fix this

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

		keyboardManager->handleEvents(quit, gameObjectContainer->player, startAnotherRound); // just pass gameObjectContainer

		// GameObjectManager
        ////////////////////////////////////////////////////////////////////////////////////////////////
        
		// update every object
        gameObjectContainer->player->update(screenManager->deltaTime);
        gameObjectContainer->barrelFactory->update(screenManager->deltaTime);
        gameObjectContainer->barrelFactory->barrelHolder->updateBarrels(screenManager->deltaTime);

		// handle collisions
        collisionResolver->handlePlayerCollision();
        collisionResolver->handleBarrelsCollision(&quit, &startAnotherRound);

        // update sprites for everyhting
        // screenManager->handlePlayerSprite(gameObjectContainer->player);

        ////////////////////////////////////////////////////////////////////////////////////////////////        
    };

    closeGame();
}

void Game::closeGame() const {
    SDL_Quit();
    exit(0);
}
