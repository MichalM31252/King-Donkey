#pragma once

#include <set>
#include <memory>
#include "GameTime.h"
#include "GameObjectContainer.h"
#include "CollisionDetector.h"
#include "../SDL2-2.0.10/include/SDL.h"

class KeyActionHandler { // rename to KeyActionHandler
public:
	std::shared_ptr<std::set<SDL_Keycode>> pressedKeys;
	std::shared_ptr<std::set<SDL_Keycode>> releasedKeys;
	std::set<SDL_Keycode> handledKeys;

	std::shared_ptr<GameTime> gameTime;
	std::shared_ptr<GameObjectContainer> gameObjectContainer;

	KeyActionHandler(std::set<SDL_Keycode>* pressedKeys, std::set<SDL_Keycode>* releasedKeys, GameTime* gameTime, GameObjectContainer* gameObjectContainer);

	void handleInput();
	void handlePressedKeys();
	void handleReleasedKeys();

	void onKeyPressArrowUp();
	void onKeyPressArrowRight();
	void onKeyPressArrowDown();
	void onKeyPressArrowLeft();
	void onKeyPressSpace();
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
};
