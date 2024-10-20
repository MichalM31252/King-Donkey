#include "GameTime.h"

GameTime::GameTime() {
	tick1 = 0;
	tick2 = 0;
	deltaTime = 0;
	worldTime = 0;
}

void GameTime::start() {
	tick1 = SDL_GetTicks();
}

void GameTime::update() {
	tick2 = SDL_GetTicks();
	deltaTime = (tick2 - tick1) * 0.001;
	tick1 = tick2;
	worldTime += deltaTime;
}