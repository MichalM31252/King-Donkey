#define _USE_MATH_DEFINES

#include "KeyCollector.h"
#include "ScreenManager.h" // temporary fix



void KeyCollector::collect(bool& quit) { // rename this to handleInput and Keyboard manager to KeyboardController or something
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
			case SDL_KEYDOWN:
                handleKeyDownCollection(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                handleKeyUpCollection(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void KeyCollector::handleKeyDownCollection(SDL_Keycode key) {
    if (pressedKeys.find(key) == pressedKeys.end()) {
        pressedKeys.insert(key);
    }
}

void KeyCollector::handleKeyUpCollection(SDL_Keycode key) {
    if (pressedKeys.find(key) != pressedKeys.end()) {
        pressedKeys.erase(key);
		releasedKeys.insert(key);
    }
}

void KeyCollector::clearReleasedKeys() {
	releasedKeys.clear();
}

std::set<SDL_Keycode> KeyCollector::getPressedKeys() {
	return pressedKeys;
}