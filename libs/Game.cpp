#include "Game.h"

Game::Game()
    : gameState(GameState::START),
    gameTime(GameTime()),
    gameObjectContainer(std::make_unique<GameObjectContainer>()),
    screenManager(ScreenManager(gameObjectContainer)),
    levelLoader(LevelLoader(gameObjectContainer)),
    keyCollector(KeyCollector()),
    startingScreenMenu(Menu(SCREEN_WIDTH - ((640 * 0.75) / 2), (SCREEN_HEIGHT - 480 * 0.75) / 2, 640 * 0.75, 480 * 0.75, 3, { "New Game", "Load Game", "Leaderboard", "Options", "Quit" })),
    pauseMenu(Menu(SCREEN_WIDTH - ((640 * 0.75) / 2), (SCREEN_HEIGHT - 480 * 0.75) / 2, 640 * 0.75, 480 * 0.75, 3, { "Resume", "Leaderboard", "Quit" })),
    gameOverMenu(Menu(SCREEN_WIDTH - ((640 * 0.75) / 2), (SCREEN_HEIGHT - 480 * 0.75) / 2, 640 * 0.75, 480 * 0.75, 3, { "Retry", "Quit" })),
    gameObjectManager(GameObjectManager(gameObjectContainer)),
    keyActionHandler(KeyActionHandler(&keyCollector.pressedKeys, &keyCollector.releasedKeys, &gameTime, gameObjectContainer.get(), &pauseMenu, &gameOverMenu, &startingScreenMenu, &gameState)) {
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
        keyCollector.collect(quit);
        keyActionHandler.handleInput();

        switch (gameState) {
            case GameState::START:
                gameTime.pause();
                screenManager.drawMenu(startingScreenMenu);
                break;

            case GameState::PAUSE:
				gameTime.pause();
                screenManager.drawMenu(pauseMenu);
                break;

            case GameState::GAME_OVER:
                screenManager.drawMenu(gameOverMenu);
                break;

            case GameState::RUNNING:
                gameTime.resume();
                gameTime.update();

                gameObjectManager.updatePositionOfGameObjects(gameTime.deltaTime);
                gameObjectManager.handleCollisionsOfGameObjects(&gameState);
                gameObjectManager.updatePhysicsOfGameObjects(gameTime.deltaTime);
                gameObjectContainer->donkeyKong->update(gameTime.deltaTime);

                if (!gameObjectContainer->player->isClimbing && gameObjectContainer->player->isJumping) {
                    gameObjectContainer->player->jump(gameTime.deltaTime);
                }

                gameObjectManager.updateSpritesOfGameObjects();

                if (!CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
                    if (!CollisionDetector::isGameObjectOnTopOfAnyPlatform(gameObjectContainer->player, gameObjectContainer->platformContainer)) {
                        if (gameObjectContainer->player->isClimbing) {
                            gameObjectContainer->player->isClimbing = false;
                            gameObjectContainer->player->currentDirectionOfMovementY = DirectionY::NONE;
                            gameObjectContainer->player->velocityY = 0;
                        }
                    }
                }

                // RENDER
                screenManager.handleFPSTimer(gameTime.deltaTime);
                screenManager.drawOutlineOfTheBoard();
                screenManager.drawAdditionalInfo(gameTime.worldTime);
                screenManager.drawElements();
                screenManager.frames++;
                break;

			case GameState::RESTART:
				levelLoader.loadLevel1();
				gameTime.reset();
				gameTime.start();
				gameState = GameState::RUNNING;
				break;

            case GameState::QUIT:
                quit = true;
                break;

            default:
                break;
        }

        screenManager.serveNextFrame();
    }

    closeGame();
}

[[noreturn]] void Game::closeGame() const {
    SDL_Quit();
    exit(0);
}
