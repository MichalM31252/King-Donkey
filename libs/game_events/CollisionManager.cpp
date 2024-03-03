extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "./CollisionManager.h"
#include "../game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "../Platform.h"
}

bool CollisionManager::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	else {
		return false;
	}
}

//bool CollisionManager::isDynamicGameObjectCollidingWithPlatform(DynamicGameObject* dynamicGameObject, Platform* platform) { // make this function check for x1 and x2 
bool CollisionManager::isPointAPartOfLine(const int x, const int y, Platform* platform) { // make this function check for x1 and x2 
	double a = platform->y2pos - platform->y1pos;
	double b = platform->x1pos - platform->x2pos;
	double c = a * platform->x1pos + b * platform->y1pos;
	
	// Ax + By = C

	// check lower-left corner
	// check lower-right corner

	// this checks 
	if ( a * x + b * y == c) { // is point part of the line
		if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) { // what's the point of this
			// is x between start and end of the platform
			// but won't the upper condition be enough??
			// no idk why
			// it's because the line we consider in the function is infinite, so we need to check if the point is between the start and end of the platform
			return true;
		}
	}

	return false;
}



bool CollisionManager::isRectInsideLadder(SDL_Rect playerDestRect, SDL_Rect ladderDestRect) { // a is player for ex, b is ladder // poor readability
	if (playerDestRect.x >= ladderDestRect.x && playerDestRect.x + playerDestRect.w <= ladderDestRect.x + ladderDestRect.w) {
		if (playerDestRect.y + playerDestRect.h <= ladderDestRect.y + ladderDestRect.h && playerDestRect.y + playerDestRect.h >= ladderDestRect.y) {
			return true;
		}
	}
	return false;
}