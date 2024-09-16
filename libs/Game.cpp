#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(std::make_unique<ScreenManager>(gameObjectContainer.get()))
    , gameObjectFactory(std::make_unique<GameObjectFactory>(gameObjectContainer.get()))
    , collisionResolver(std::make_unique<CollisionResolver>(gameObjectContainer.get(), screenManager.get()))
    , roundManager(std::make_unique<RoundManager>(screenManager.get(), gameObjectFactory.get(), gameObjectContainer.get(), collisionResolver.get()))
{
}

void Game::initGame() {
    screenManager->createSDL();
    screenManager->createFramerate();
	int startAnotherRound = 0;
    roundManager->handleRound(startAnotherRound);
    closeGame();
}

void Game::closeGame() const {
    SDL_Quit();
    exit(0);
}

// Implement this in the future
//void Game::closeGame(ScreenManager& screenManager) const { // change this into a vector to be more efficient (so it can destroy every gameobject)
//	SDL_FreeSurface(screenManager.charset);
//	SDL_FreeSurface(screenManager.screen);
//	SDL_DestroyTexture(screenManager.scrtex);
//	SDL_DestroyWindow(screenManager.window);
//	SDL_DestroyRenderer(screenManager.renderer);
//	SDL_Quit();
//	exit(0);
//}
