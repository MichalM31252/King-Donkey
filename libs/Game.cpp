#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(std::make_unique<ScreenManager>(gameObjectContainer.get()))
	, levelLoader(std::make_unique<LevelLoader>(gameObjectContainer.get()))
	, keyboardManager(std::make_unique<KeyboardManager>(gameObjectContainer.get()))
	, gameObjectManager(std::make_unique<GameObjectManager>(gameObjectContainer.get()))
{
}

[[noreturn]] void Game::initGame() const {
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

		keyboardManager->handleEvents(quit, startAnotherRound);

        gameObjectManager->updatePositionOfGameObjects(screenManager->deltaTime);
		gameObjectManager->handleCollisionsOfGameObjects(quit, startAnotherRound);
		gameObjectManager->updateSpritesOfGameObjects();
		gameObjectManager->updatePhysicsOfGameObjects(screenManager->deltaTime);

        // no idea where to put this, this updates the class that creates barrels
        gameObjectContainer->donkeyKong->update(screenManager->deltaTime);

        // no idea where to put this
        if (!gameObjectContainer->player->isClimbing && gameObjectContainer->player->isJumping) {
            gameObjectContainer->player->jump(screenManager->deltaTime);
        }
    }

    closeGame();
}

[[noreturn]] void Game::closeGame() const {
    SDL_Quit();
    exit(0);
}
