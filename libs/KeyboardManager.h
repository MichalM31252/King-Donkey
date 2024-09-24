#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "CollisionDetector.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class KeyboardManager {
public:
    SDL_Event event;
    GameObjectContainer* gameObjectContainer;

    KeyboardManager();
    explicit KeyboardManager(GameObjectContainer* gameObjectContainer);

    void handleEvents(bool& quit, int& startAnotherRound);

    static void initializeQuit(bool& quit, int& startAnotherRound);

    void onKeyPressed(bool& quit, int& startAnotherRound);
    void onKeyPressArrowUp();
    void onKeyPressArrowRight();
    void onKeyPressArrowDown();
    void onKeyPressArrowLeft();
    void onKeyPressSpace();
    static void onKeyPressN(bool& quit, int& startAnotherRound);
    static void onKeyPress1(bool& quit, int& startAnotherRound);
    static void onKeyPress2(bool& quit, int& startAnotherRound);
    static void onKeyPress3(bool& quit, int& startAnotherRound);

    void onKeyReleased();

    void onKeyReleasedArrowUp();
    void onKeyReleasedArrowRight();
    void onKeyReleasedArrowDown();
    void onKeyReleasedArrowLeft();
};