#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameTime(GameTime())
    , gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(ScreenManager(gameObjectContainer.get()))
	, levelLoader(LevelLoader(gameObjectContainer.get()))
	, keyboardManager(KeyboardManager(gameObjectContainer.get(), &gameTime))
	, gameObjectManager(GameObjectManager(gameObjectContainer.get()))
{
	startGame();
}

[[noreturn]] void Game::startGame() {
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
	gameTime.start();
    runGame();
}

[[noreturn]] void Game::runGame() {
    bool quit = false;
    while (!quit) {

		// PROCESS EVENTS
		keyboardManager.handleEvents(quit);

        if (!gameTime.isPaused) {
            // UPDATE TIME
            gameTime.update();

            // UPDATE GAMEOBJECTS
            gameObjectManager.updatePositionOfGameObjects(gameTime.deltaTime);
            gameObjectManager.handleCollisionsOfGameObjects(quit);
            gameObjectManager.updatePhysicsOfGameObjects(gameTime.deltaTime);
            // no idea where to put this, this updates the class that creates barrels
            gameObjectContainer->donkeyKong->update(gameTime.deltaTime);

            // no idea where to put this
            if (!gameObjectContainer->player->isClimbing && gameObjectContainer->player->isJumping) {
                gameObjectContainer->player->jump(gameTime.deltaTime);
            }

            // RENDER
            gameObjectManager.updateSpritesOfGameObjects(gameTime.deltaTime); // handle animations?
            screenManager.handleFPSTimer(gameTime.deltaTime);
            screenManager.drawOutlineOfTheBoard();
            screenManager.drawAdditionalInfo(gameTime.worldTime);
            screenManager.drawElements(); // current quick fix is that ladder is drawn first then player to make player appear on top of ladder
            screenManager.serveNextFrame();
            screenManager.frames++;
        }
    }
    closeGame();
}

[[noreturn]] void Game::closeGame() {
    SDL_Quit();
    exit(0);
}
