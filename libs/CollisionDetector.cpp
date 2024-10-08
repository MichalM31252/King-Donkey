#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

bool CollisionDetector::isXWithinWidthOfPlatform(const int x, const Platform* platform) {
	if ((x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos)) {
		return true;
	}
	return false;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const GameObject* gameObject, const PlatformContainer* platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectOnTopOfPlatform(const GameObject* gameObject, const Platform* platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomRightCorner, platform)) {
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomLeftCorner, platform)) {
        return true;
    }

    return false;
}

bool CollisionDetector::isPointAPartOfLine(const int x, const int y, const Platform* platform) { // create class Point ?
    double a = platform->y2pos - platform->y1pos;
    double b = platform->x1pos - platform->x2pos;
    double c = a * platform->x1pos + b * platform->y1pos;

    if (a * x + b * y == c) {
        return true;
    }
    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(const GameObject* gameObject, const Platform* platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomLeftCorner, platform)) {
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomRightCorner, platform) ) {
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectInsideAnyLadder(const GameObject* gameObject, const LadderContainer* ladderContainer) {
    for (int i = 0; i < ladderContainer->getNumberOfElements(); i++) {
        if (isGameObjectInsideLadder(gameObject, ladderContainer->ladders[i])) {
            return true;
        }
    }
    return false;
}

// it needs to be completely inside the rect and not just collision
bool CollisionDetector::isGameObjectInsideLadder(const GameObject* gameObject, const GameObject* ladder) { 
    if (((gameObject->xpos >= ladder->xpos && gameObject->xpos < ladder->xpos + ladder->destRect.w) && (gameObject->xpos + gameObject->destRect.w > ladder->xpos && gameObject->xpos + gameObject->destRect.w < ladder->xpos + ladder->destRect.w))) {
        if (isCollisionBetweenRects(gameObject->destRect, ladder->destRect)) {
            return true;
        }
    }
    return false;
}

