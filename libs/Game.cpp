#define _USE_MATH_DEFINES

#include "Game.h"
#include "CollisionResolver.h" // temporary fix

Game::Game()
    : gameTime(GameTime())
    , gameObjectContainer(std::make_unique<GameObjectContainer>())
    , screenManager(ScreenManager(gameObjectContainer))
    , levelLoader(LevelLoader(gameObjectContainer))
    , keyCollector(KeyCollector())
    , pauseMenu(Menu(SCREEN_WIDTH - (640 * 0.75 / 2), (SCREEN_HEIGHT - 480 * 0.75) / 2, 640 * 0.75, 480 * 0.75, 3))
    , gameObjectManager(GameObjectManager(gameObjectContainer))
    , keyActionHandler(KeyActionHandler(&keyCollector.pressedKeys, &keyCollector.releasedKeys, &gameTime, gameObjectContainer.get(), &pauseMenu))
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

		// collect currently pressed keys
		keyCollector.collect(quit);
        keyActionHandler.handleInput();

        // to be honest there should be a class for just handling the input 
        // there should be a class for deleting specific keys

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

            if (!CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
                if (CollisionDetector::isGameObjectOnTopOfAnyPlatform(gameObjectContainer->player, gameObjectContainer->platformContainer)) {
                    if (gameObjectContainer->player->isClimbing) {
                        gameObjectContainer->player->isClimbing = false;
						gameObjectContainer->player->currentDirectionOfMovementY = DirectionY::NONE;
						gameObjectContainer->player->velocityY = 0;
                    }
                }
            }

            // RENDER
            gameObjectManager.updateSpritesOfGameObjects(); // handle animations?
            screenManager.handleFPSTimer(gameTime.deltaTime);
            screenManager.drawOutlineOfTheBoard();
            screenManager.drawAdditionalInfo(gameTime.worldTime);
            screenManager.drawElements(); // current quick fix is that ladder is drawn first then player to make player appear on top of ladder
            screenManager.frames++;
        }
        else {
			screenManager.drawMenu(pauseMenu.selectedOption);
        }
        screenManager.serveNextFrame();
    }
    closeGame();
}

[[noreturn]] void Game::closeGame() const {
    SDL_Quit();
    exit(0);
}
