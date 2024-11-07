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

// create one collector for keys pressed and released during the game, and one during the pause 

class KeyCollector {
public:
    SDL_Event event;
    std::set<SDL_Keycode> pressedKeys;
    std::set<SDL_Keycode> releasedKeys;

    KeyCollector() = default;

    void collect(bool& quit);
    void handlePressedKeysCollection(SDL_Keycode key);
    void handleReleasedKeysCollection(SDL_Keycode key);

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