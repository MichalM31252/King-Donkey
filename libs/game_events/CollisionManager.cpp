extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./CollisionManager.h"
}

bool CollisionManager::checkCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionManager::checkObjectCollisionWithPlatform(double xposObject, double yposObject, int hObject, double x1Platform, double y1Platform, double x2Platform, double y2Platform) {
	double a = y2Platform - y1Platform;
	double b = x1Platform - x2Platform;
	double c = a * x1Platform + b * y1Platform;
	// Ax + By = C

	if ( a * xposObject + b * yposObject == c) {
		if ((xposObject >= x1Platform && xposObject <= x2Platform) || (xposObject <= x1Platform && xposObject >= x2Platform)) {
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkIfInsideLadder(SDL_Rect a, SDL_Rect b) { // a is player for ex, b is ladder
	if (a.x >= b.x && a.x + a.w <= b.x + b.w) {
		if (a.y + a.h <= b.y + b.h && a.y + a.h >= b.y) {
			return true;
		}
	}
	return false;
}