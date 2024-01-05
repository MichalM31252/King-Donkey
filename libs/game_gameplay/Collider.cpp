extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../../libs/game_gameplay/Collider.h"
}

void Collider::checkCollision(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		isColliding = true;
	}
	else {
		isColliding = false;
	}
}