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

	// so basically a platform can only have a function that to an integer argument always returns an integer value 
	if ( a * xposObject + b * yposObject == c) { // if ( a * xposObject + b * yposObject == c) {
		// yes player is inside this layer // FUCK LAYERS AFTER EACH PIXEL MOVED CHECK IF HE PASSED THE LINE
		// move him one pixel above the top layer on this x
		
		// okay lets hope 1 layer is enough for now 
		// just move him 1 pixel higher

		// if you want to make it right change the y to 
		// double y = ((-1.0 * a * xposPlayer) - c) / b; // move player to this // nah this is the y on the line

		if ((xposObject >= x1Platform && xposObject <= x2Platform) || (xposObject <= x1Platform && xposObject >= x2Platform)) { // stays in the width of the platform
			printf("COLLIDING\n");
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkIfInsideLadder(SDL_Rect a, SDL_Rect b) { // a is player for ex, b is ladder for example
	if (a.x >= b.x && a.x + a.w <= b.x + b.w) { // on the right side of b && and on the left side of right part of b 
		// this if doesnt work 
		// WHY B.Y IS 100px it should be 170px
		if (a.y + a.h <= b.y + b.h && a.y + a.h >= b.y) { // above or on the same level as bottom of the ladder && below the top of the ladder 
			// for now this wont let the player get on top of the ladder 
			return true;
		}
	}
	return false;
}