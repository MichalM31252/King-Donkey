#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "CollisionDetector.h"
#include "GameTime.h"
#include <set>
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class KeyCollector { // rename to key collector and collect pressed and released keys
public:
    SDL_Event event;
    std::set<SDL_Keycode> pressedKeys;
    std::set<SDL_Keycode> releasedKeys;

    KeyCollector() = default;

    void collect(bool& quit);
    void handleKeyDownCollection(SDL_Keycode key);
    void handleKeyUpCollection(SDL_Keycode key);

	void clearReleasedKeys();

    std::set<SDL_Keycode> getPressedKeys();

    // static void initializeQuit(bool& quit);

    //void onKeyPressArrowUp();
    //void onKeyPressArrowRight();
    //void onKeyPressArrowDown();
    //void onKeyPressArrowLeft();
    //void onKeyPressSpace();
    //void onKeyPressEsc();
    //void onKeyPressN(bool& quit);
    //void onKeyPress1(bool& quit);
    //void onKeyPress2(bool& quit);
    //void onKeyPress3(bool& quit);

    //void onKeyReleasedArrowUp();
    //void onKeyReleasedArrowRight();
    //void onKeyReleasedArrowDown();
    //void onKeyReleasedArrowLeft();
};