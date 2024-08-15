#pragma once

extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "Player.h"
#include "Constants.h"
#include "GameObjectContainer.h"
}

class KeyboardManager {
private:
	SDL_Event event; // this can be used here
public:
    std::unique_ptr<GameObjectContainer> gameObjectContainer;

    KeyboardManager();
    explicit KeyboardManager(std::unique_ptr<GameObjectContainer> gameObjectContainer);

    void handleEvents(bool& quit, double deltaTime, std::unique_ptr<Player>& player, int& startAnotherRound);

    static void initializeQuit(bool& quit, int& startAnotherRound);

    void onKeyPressed(bool& quit, double deltaTime, std::unique_ptr<Player>& player, int& startAnotherRound);
    static void onKeyPressArrowUp(double deltaTime, std::unique_ptr<Player>& player);
    static void onKeyPressArrowRight(double deltaTime, std::unique_ptr<Player>& player);
    static void onKeyPressArrowDown(double deltaTime, std::unique_ptr<Player>& player);
    static void onKeyPressArrowLeft(double deltaTime, std::unique_ptr<Player>& player);
    static void onKeyPressSpace(std::unique_ptr<Player>& player);
    static void onKeyPressN(bool& quit, int& startAnotherRound);
    static void onKeyPress1(bool& quit, int& startAnotherRound);
    static void onKeyPress2(bool& quit, int& startAnotherRound);
    static void onKeyPress3(bool& quit, int& startAnotherRound);

    void onKeyReleased(std::unique_ptr<Player>& player);

    static void onKeyReleasedArrowUp(std::unique_ptr<Player>& player);
    static void onKeyReleasedArrowRight(std::unique_ptr<Player>& player);
    static void onKeyReleasedArrowDown(std::unique_ptr<Player>& player);
    static void onKeyReleasedArrowLeft(std::unique_ptr<Player>& player);
};