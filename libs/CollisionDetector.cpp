#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

bool CollisionDetector::isPointAPartOfLine(const int x, const int y, Platform* platform) { // create class Point ?
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

bool CollisionDetector::isRectInsideLadder(SDL_Rect playerDestRect, SDL_Rect ladderDestRect) {
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

bool CollisionDetector::isGameObjectInsidePlatform(GameObject* gameObject, Platform* platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, platform)) {
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, platform)) {
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(GameObject* gameObject, PlatformHolder* platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
            return true;
        }
    }
    return false;
}