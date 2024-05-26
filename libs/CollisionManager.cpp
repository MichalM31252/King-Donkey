extern "C" {
#include "CollisionManager.h"
}

CollisionManager::CollisionManager() {
	this->gameObjectContainer = GameObjectContainer();
}

CollisionManager::CollisionManager(GameObjectContainer& gameObjectContainer) {
	this->gameObjectContainer = gameObjectContainer;
}

bool CollisionManager::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	else {
		return false;
	}
}

bool CollisionManager::isPointAPartOfLine(const int x, const int y, Platform* platform) { // make this function check for x1 and x2 
	double a = platform->y2pos - platform->y1pos;
	double b = platform->x1pos - platform->x2pos;
	double c = a * platform->x1pos + b * platform->y1pos;
	
	// Ax + By = C
	if ( a * x + b * y == c) { // is point part of the line
		if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) {
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