#pragma once

#include <set>
#include <memory>
#include "GameTime.h"
#include "GameObjectContainer.h"
#include "CollisionDetector.h"
#include "Menu.h"
#include "GameState.h"
#include "../SDL2-2.0.10/include/SDL.h"


class KeyActionHandler {
public:
	std::shared_ptr<std::set<SDL_Keycode>> pressedKeys;
	std::shared_ptr<std::set<SDL_Keycode>> releasedKeys;
	std::set<SDL_Keycode> handledKeys;

	std::shared_ptr<GameTime> gameTime;
	std::shared_ptr<GameObjectContainer> gameObjectContainer;
	std::shared_ptr<Menu> pauseMenu;
	GameState* gameState;

	KeyActionHandler(std::set<SDL_Keycode>* pressedKeys, std::set<SDL_Keycode>* releasedKeys, GameTime* gameTime, GameObjectContainer* gameObjectContainer, Menu* pauseMenu, GameState* gameState);

	void handleInput();
	void handlePressedKeys();
	void handleReleasedKeys();

	void onKeyPressArrowUp();
	void onKeyPressArrowRight();
	void onKeyPressArrowDown();
	void onKeyPressArrowLeft();
	void onKeyPressSpace();
	void onKeyPressEnter();
	void onKeyPressEsc();

	void onKeyReleasedArrowUp();
	void onKeyReleasedArrowRight();
	void onKeyReleasedArrowDown();
	void onKeyReleasedArrowLeft();

	void deleteHandledKey(SDL_Keycode key);
	void deleteReleasedKey(SDL_Keycode key);
	void deletePressedKey(SDL_Keycode key);

	void moveAllPressedKeysToReleasedKeys();
	void moveAllHandledKeysToReleasedKeys();

	void handleMenuSelection();
};
