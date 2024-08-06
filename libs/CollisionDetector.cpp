#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
	if (SDL_HasIntersection(&a, &b)) {
		return true;
	}
	return false;
}

bool CollisionDetector::isPointAPartOfLine(const int x, const int y, Platform* platform) { // make this function check for x1 and x2 
	double a = platform->y2pos - platform->y1pos;
	double b = platform->x1pos - platform->x2pos;
	double c = a * platform->x1pos + b * platform->y1pos;

	// Ax + By = C
	if (a * x + b * y == c) { // is point part of the line
		if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) {
			return true;
		}
	}
	return false;
}

bool CollisionDetector::isRectInsideLadder(SDL_Rect playerDestRect, SDL_Rect ladderDestRect) { // a is player for ex, b is ladder // poor readability
	if (playerDestRect.x >= ladderDestRect.x && playerDestRect.x + playerDestRect.w <= ladderDestRect.x + ladderDestRect.w) {
		if (playerDestRect.y + playerDestRect.h <= ladderDestRect.y + ladderDestRect.h && playerDestRect.y + playerDestRect.h >= ladderDestRect.y) {
			return true;
		}
	}
	return false;
}

bool CollisionDetector::isGameObjectOnTopOfPlatform(GameObject* gameObject, Platform* platform) {
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, platform)) {
		return true;
	}

	if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, platform)) {
		return true;
	}

	return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(GameObject* gameObject, Platform* platform) { // refactor to boxes instead of pixels
	int yPosition = gameObject->ypos + gameObject->destRect.h;
	int xPositionBottomLeftCorner = gameObject->xpos;
	int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

	if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, platform)) { // check bottom left corner
		return true;
	}

	if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, platform)) { // check bottom right corner
		return true;
	}

	return false;
}

bool CollisionDetector::isGameObjectInsideAnyPlatform(GameObject* gameObject, PlatformHolder* platformHolder) {
	for (int i = 0; i < platformHolder->numberOfElements; i++) {
		if (CollisionDetector::isGameObjectInsidePlatform(gameObject, &platformHolder->platforms[i])) {
			return true;
		}
	}
	return false;
}