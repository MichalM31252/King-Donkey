#include "GameTime.h"

GameTime::GameTime() {
    tick1 = 0;
    tick2 = 0;
    deltaTime = 0;
    worldTime = 0;
    isPaused = false;
}

void GameTime::start() {
    tick1 = SDL_GetTicks();
    isPaused = false;
}

void GameTime::update() {
    if (!isPaused) {
        tick2 = SDL_GetTicks();
        deltaTime = (tick2 - tick1) * 0.001;
        tick1 = tick2;
        worldTime += deltaTime;
    }
}

void GameTime::reset() {
    tick1 = SDL_GetTicks();
    tick2 = tick1;
    deltaTime = 0;
    worldTime = 0;
    isPaused = false;
}

void GameTime::pause() {
    if (!isPaused) {
        isPaused = true;
        tick2 = SDL_GetTicks();
    }
}

void GameTime::resume() {
    if (isPaused) {
        isPaused = false;
        tick1 += SDL_GetTicks() - tick2;
    }
}

