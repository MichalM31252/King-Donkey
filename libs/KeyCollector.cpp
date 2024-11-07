#define _USE_MATH_DEFINES

#include "KeyCollector.h"
#include "ScreenManager.h" // temporary fix



void KeyCollector::collect(bool& quit) { // rename this to handleInput and Keyboard manager to KeyboardController or something
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_KEYDOWN && !event.key.repeat) {
            handlePressedKeysCollection(event.key.keysym.sym);
        }
        if (event.type == SDL_KEYUP) {
            handleReleasedKeysCollection(event.key.keysym.sym);
		}
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        break;
    }
}

void KeyCollector::handlePressedKeysCollection(SDL_Keycode key) {
    if (pressedKeys.find(key) == pressedKeys.end()) {
        pressedKeys.insert(key);
    }
}

void KeyCollector::handleReleasedKeysCollection(SDL_Keycode key) {
    if (pressedKeys.find(key) != pressedKeys.end()) {
        pressedKeys.erase(key);
		releasedKeys.insert(key);
    }
}

std::set<SDL_Keycode> KeyCollector::getPressedKeys() {
	return pressedKeys;
}