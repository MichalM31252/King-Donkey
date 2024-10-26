#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "CollisionDetector.h"
#include "GameTime.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class KeyboardInputManager {
public:
    SDL_Event event;
    GameObjectContainer* gameObjectContainer;
    GameTime* gameTime;

    KeyboardInputManager() = default;
    KeyboardInputManager(GameObjectContainer* gameObjectContainer, GameTime* gameTime);

    void handleEvents(bool& quit);

    static void initializeQuit(bool& quit);

    void onKeyPressed(bool& quit);
    void onKeyPressArrowUp();
    void onKeyPressArrowRight();
    void onKeyPressArrowDown();
    void onKeyPressArrowLeft();
    void onKeyPressSpace();
    void onKeyPressP();

    static void onKeyPressN(bool& quit);
    static void onKeyPress1(bool& quit);
    static void onKeyPress2(bool& quit);
    static void onKeyPress3(bool& quit);

    void onKeyReleased();

    void onKeyReleasedArrowUp();
    void onKeyReleasedArrowRight();
    void onKeyReleasedArrowDown();
    void onKeyReleasedArrowLeft();
};