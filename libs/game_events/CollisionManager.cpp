extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./CollisionManager.h"
}

void Collider::checkCollision(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		isColliding = true;
	}
	else {
		isColliding = false;
	}
}

bool Collider::checkPlayerCollisionWithPlatform(double xposObject, double yposObject, int hObject, double x1Platform, double y1Platform, double x2Platform, double y2Platform) {
	double a = y2Platform - y1Platform;
	double b = x1Platform - x2Platform;
	double c = a * x1Platform + b * y1Platform;
	// Ax + By = C

	// so basically a platform can only have a function that to an integer argument always returns an integer value 
	if ( a * xposObject + b * yposObject == c) { // if ( a * xposObject + b * yposObject == c) {
		// yes player is inside this layer
		// move him one pixel above the top layer on this x
		
		// okay lets hope 1 layer is enough for now 
		// just move him 1 pixel higher
		if ((xposObject >= x1Platform && xposObject <= x2Platform) || (xposObject <= x1Platform && xposObject >= x2Platform)) { // stays in the width of the platform
			printf("COLLIDING\n");
			return true;
		}
	}

	// double y = ((-1.0 * a * xposPlayer) - c) / b; // move player to this // nah this is the y on the line
}