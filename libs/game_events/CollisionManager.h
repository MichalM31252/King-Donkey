#pragma once
extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
	// add here game object
}

class CollisionManager {
public:
	bool isColliding = false;
	bool checkCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	bool checkObjectCollisionWithPlatform(double xposObject, double yposObject, int hObject, double x1Platform, double y1Platform, double x2Platform, double y2Platform);
	bool checkIfInsideLadder(SDL_Rect a, SDL_Rect b);
};