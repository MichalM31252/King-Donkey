#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

bool CollisionDetector::isPointWithinWidthOfPlatform(const int x, const int y, const Platform* platform) {
	if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) {
		return true;
	}
	return false;

}

bool CollisionDetector::isPointAPartOfLine(const int x, const int y, const Platform* platform) { // create class Point ?
    double a = platform->y2pos - platform->y1pos;
    double b = platform->x1pos - platform->x2pos;
    double c = a * platform->x1pos + b * platform->y1pos;

    if (a * x + b * y == c) { // is point part of the line
        return true;
    }
    return false;
}

bool CollisionDetector::isRectInsideLadder(const SDL_Rect playerDestRect, const SDL_Rect ladderDestRect) {
    if (playerDestRect.x >= ladderDestRect.x && playerDestRect.x + playerDestRect.w <= ladderDestRect.x + ladderDestRect.w) {
        if (playerDestRect.y + playerDestRect.h <= ladderDestRect.y + ladderDestRect.h && playerDestRect.y + playerDestRect.h >= ladderDestRect.y) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectOnTopOfPlatform(const GameObject* gameObject, const Platform* platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, platform) && CollisionDetector::isPointWithinWidthOfPlatform(xPositionBottomRightCorner, yPosition + 1, platform)) {
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, platform) && CollisionDetector::isPointWithinWidthOfPlatform(xPositionBottomLeftCorner, yPosition + 1, platform)) {
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(const GameObject* gameObject, const Platform* platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, platform) && CollisionDetector::isPointWithinWidthOfPlatform(xPositionBottomLeftCorner, yPosition, platform)) {
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, platform) && CollisionDetector::isPointWithinWidthOfPlatform(xPositionBottomRightCorner, yPosition, platform) ) {
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const GameObject* gameObject, const PlatformHolder* platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
            return true;
        }
    }
    return false;
}