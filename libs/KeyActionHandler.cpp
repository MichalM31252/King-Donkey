#include "KeyActionHandler.h"

KeyActionHandler::KeyActionHandler(std::set<SDL_Keycode> pressedKeys, std::set<SDL_Keycode> releasedKeys, GameTime* gameTime, GameObjectContainer* gameObjectContainer)
	: pressedKeys(pressedKeys)
	, releasedKeys(releasedKeys)
	, gameTime(gameTime)
	, gameObjectContainer(gameObjectContainer)
{
}

//void PressedKeyActionHandler::handleInput() {
//	for (auto key : *pressedKeys) {
//		switch (key) {
//			case SDLK_UP:
//				onKeyPressArrowUp();
//				break;
//			case SDLK_DOWN:
//				onKeyPressArrowDown();
//				break;
//			case SDLK_LEFT:
//				onKeyPressArrowLeft();
//				break;
//			case SDLK_RIGHT:
//				onKeyPressArrowRight();
//				break;
//			case SDLK_SPACE:
//				onKeyPressSpace();
//				break;
//			case SDLK_ESCAPE:
//				onKeyPressEsc();
//				break;
//			default:
//				break;
//		}
//	}
//}

//void PressedKeyActionHandler::onKeyPressArrowUp() {
//	if (!gameTime->isPaused) {
//		auto player = gameObjectContainer->player;
//		if (CollisionDetector::isGameObjectInsideAnyLadder(gameObjectContainer->player, gameObjectContainer->ladderContainer)) {
//			player->isClimbing = true;
//			player->isFalling = false;
//			player->isJumping = false;
//			player->currentDirectionOfMovementY = DirectionY::UP;
//			player->velocityY = DEFAULT_PLAYER_SPEED;
//		}
//		else {
//			player->isClimbing = false;
//			player->currentDirectionOfMovementY = DirectionY::NONE;
//			player->velocityY = 0;
//		}
//	}
//}

//void KeyboardInputManager::onKeyReleasedArrowUp() {
//    if (!gameTime->isPaused) {
//        gameObjectContainer->player->accumulatedMoveUp = 0;
//        if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::UP) {
//            gameObjectContainer->player->velocityY = 0;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyReleasedArrowLeft() {
//    if (!gameTime->isPaused) {
//        gameObjectContainer->player->accumulatedMoveLeft = 0;
//        if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::LEFT) {
//            gameObjectContainer->player->velocityX = 0;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyReleasedArrowRight() {
//    if (!gameTime->isPaused) {
//        gameObjectContainer->player->accumulatedMoveRight = 0;
//        if (gameObjectContainer->player->currentDirectionOfMovementX == DirectionX::RIGHT) {
//            gameObjectContainer->player->velocityX = 0;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyReleasedArrowDown() {
//    if (!gameTime->isPaused) {
//        gameObjectContainer->player->accumulatedMoveDown = 0;
//	    if (gameObjectContainer->player->currentDirectionOfMovementY == DirectionY::DOWN) {
//		    gameObjectContainer->player->velocityY = 0;
//	    }
//    }
//}
//
//void KeyboardInputManager::initializeQuit(bool& quit) {
//	quit = true;
//}


//
//void KeyboardInputManager::onKeyPressArrowDown() {
//    if (!gameTime->isPaused) {
//        auto player = gameObjectContainer->player;
//        if (CollisionDetector::isGameObjectInsideAnyLadder(player, gameObjectContainer->ladderContainer)) {
//            player->isClimbing = true;
//            player->isFalling = false;
//            player->isJumping = false;
//            player->currentDirectionOfMovementY = DirectionY::DOWN;
//            player->velocityY = DEFAULT_PLAYER_SPEED;
//        }
//        else {
//            player->isClimbing = false;
//            player->currentDirectionOfMovementY = DirectionY::NONE;
//            player->velocityY = 0;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyPressArrowLeft() {
//    if (!gameTime->isPaused) {
//        auto player = gameObjectContainer->player;
//        if (!player->isClimbing) {
//            player->currentDirectionOfMovementX = DirectionX::LEFT;
//            player->velocityX = DEFAULT_PLAYER_SPEED;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyPressArrowRight() {
//    if (!gameTime->isPaused) {
//        auto player = gameObjectContainer->player;
//        if (!player->isClimbing) {
//            player->currentDirectionOfMovementX = DirectionX::RIGHT;
//            player->velocityX = DEFAULT_PLAYER_SPEED;
//        }
//    }
//}
//
//void KeyboardInputManager::onKeyPressSpace() {
//    if (!gameTime->isPaused) {
//        gameObjectContainer->player->initJump();
//    }
//}
//
//void KeyboardInputManager::onKeyPressN(bool& quit) {
//    if (!gameTime->isPaused) {
//        onKeyPress1(quit);
//    }
//}
//
//void KeyboardInputManager::onKeyPressEsc() {
//    if (!gameTime->isPaused) {
//        gameTime->pause();
//        // show menu
//
//    }
//    else {
//        gameTime->resume();
//		// hide menu
//    }
//}
//
//void KeyboardInputManager::onKeyPress1(bool& quit) {
//    if (!gameTime->isPaused) {
//        quit = true;
//    }
//}
//
//void KeyboardInputManager::onKeyPress2(bool& quit) {
//    if (!gameTime->isPaused) {
//        onKeyPress1(quit);
//    }
//}
//
//void KeyboardInputManager::onKeyPress3(bool& quit) {
//    if (!gameTime->isPaused) {
//        onKeyPress1(quit);
//    }
//}