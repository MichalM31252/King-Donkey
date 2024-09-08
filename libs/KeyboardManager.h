#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

class KeyboardManager {
public:
    SDL_Event event; // this can be used here
    GameObjectContainer* gameObjectContainer;

    KeyboardManager();
    explicit KeyboardManager(GameObjectContainer* gameObjectContainer);

    void handleEvents(bool& quit, Player* player, int& startAnotherRound);

    static void initializeQuit(bool& quit, int& startAnotherRound);

    void onKeyPressed(bool& quit, Player* player, int& startAnotherRound) const;
    static void onKeyPressArrowUp(Player* player);
    static void onKeyPressArrowRight(Player* player);
    static void onKeyPressArrowDown(Player* player);
    static void onKeyPressArrowLeft(Player* player);
    static void onKeyPressSpace(Player* player);
    static void onKeyPressN(bool& quit, int& startAnotherRound);
    static void onKeyPress1(bool& quit, int& startAnotherRound);
    static void onKeyPress2(bool& quit, int& startAnotherRound);
    static void onKeyPress3(bool& quit, int& startAnotherRound);

    void onKeyReleased(Player* player) const;

    static void onKeyReleasedArrowUp(Player* player);
    static void onKeyReleasedArrowRight(Player* player);
    static void onKeyReleasedArrowDown(Player* player);
    static void onKeyReleasedArrowLeft(Player* player);
};