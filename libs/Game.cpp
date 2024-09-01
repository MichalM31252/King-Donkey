#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameObjectContainer(new GameObjectContainer())
    , screenManager(new ScreenManager(gameObjectContainer))
    , gameObjectFactory(new GameObjectFactory(gameObjectContainer))
    , collisionResolver(new CollisionResolver(gameObjectContainer, screenManager))
    , roundManager(new RoundManager(screenManager, gameObjectFactory, gameObjectContainer, collisionResolver))
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
