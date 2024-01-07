#pragma once
extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
}

class Collider {
public:
	bool isColliding = false;
	void checkCollision(SDL_Rect a, SDL_Rect b);
	void checkPlayerCollisionWithLayerOfPlatform(double xposObject, double yposObject, int hObject, double x1Platform, double y1Platform, double x2Platform, double y2Platform);
};