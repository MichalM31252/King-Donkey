#define _USE_MATH_DEFINES

extern "C" {
#include "Game.h"
#include "CollisionResolver.h" // temporary fix
}

Game::Game() {

	// the only thing that should be here is the stage manager
	// first move every method from this class to its respective manager then implement the stage manager

	GameObjectContainer* gameObjectC = new GameObjectContainer();
	gameObjectContainer = gameObjectC;

	ScreenManager* screenMan = new ScreenManager(gameObjectContainer);
	screenManager = screenMan;

	GameObjectFactory* gameObjectMan = new GameObjectFactory(gameObjectContainer);
	gameObjectFactory = gameObjectMan;

	CollisionResolver* collisionMan = new CollisionResolver(gameObjectContainer, screenManager);
	collisionResolver = collisionMan;

	RoundManager* roundMan = new RoundManager(screenManager, gameObjectFactory, gameObjectContainer, collisionResolver);
	roundManager = roundMan;
}

void Game::initGame() {
	screenManager->createSDL();

	int startAnotherRound = 0;

	roundManager->handleRound(startAnotherRound);

	closeGame();
}

void Game::closeGame() {
	SDL_Quit();
	exit(0);
}

// Implement this in the future
//void Game::closeGame(ScreenManager& screenManager) { // change this into a vector to be more efficient (so it can destroy every gameobject)
//	SDL_FreeSurface(screenManager.charset);
//	SDL_FreeSurface(screenManager.screen);
//	SDL_DestroyTexture(screenManager.scrtex);
//	SDL_DestroyWindow(screenManager.window);
//	SDL_DestroyRenderer(screenManager.renderer);
//	SDL_Quit();
//	exit(0);
//}
