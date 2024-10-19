#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(ScreenManager(gameObjectContainer.get()))
	, levelLoader(LevelLoader(gameObjectContainer.get()))
	, keyboardManager(KeyboardManager(gameObjectContainer.get()))
	, gameObjectManager(GameObjectManager(gameObjectContainer.get()))
{
}

[[noreturn]] void Game::initGame() {
    screenManager.checkSDL();
    screenManager.createWindowAndRenderer();
    screenManager.setHint();
    screenManager.setRenderLogicalSize();
    screenManager.setDefaultDrawColor();
    screenManager.setWindowTitle();
    screenManager.setCharset();
    screenManager.setScreen();
    screenManager.setTexture();
    screenManager.hideCursor();
    screenManager.setColorKey();
    screenManager.setColors();
    screenManager.createFramerate();
     
	levelLoader.loadLevel1();

    bool quit = false;
    while (!quit) {
		// UPDATE TIME
        screenManager.handleDifferentComputers();

		// PROCESS EVENTS
		keyboardManager.handleEvents(quit);

        // UPDATE
        gameObjectManager.updatePositionOfGameObjects(screenManager.deltaTime);
		gameObjectManager.handleCollisionsOfGameObjects(quit);
		gameObjectManager.updatePhysicsOfGameObjects(screenManager.deltaTime);

        // no idea where to put this, this updates the class that creates barrels
        gameObjectContainer->donkeyKong->update(screenManager.deltaTime);

        // no idea where to put this
        if (!gameObjectContainer->player->isClimbing && gameObjectContainer->player->isJumping) {
            gameObjectContainer->player->jump(screenManager.deltaTime);
        }

        // RENDER
        screenManager.updateWorldTime();
        screenManager.handleFPSTimer();
        screenManager.drawOutlineOfTheBoard();
        screenManager.drawAdditionalInfo();
		screenManager.drawElements(); // current quick fix is that ladder is drawn first then player to make player appear on top of ladder
        screenManager.serveNextFrame();
        screenManager.frames++;
        gameObjectManager.updateSpritesOfGameObjects(screenManager.deltaTime); // handle animations?
    }
    closeGame();
}

[[noreturn]] void Game::closeGame() {
    SDL_Quit();
    exit(0);
}
