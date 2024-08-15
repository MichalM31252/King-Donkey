#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

bool CollisionDetector::isPointAPartOfLine(const int x, const int y, std::unique_ptr<Platform> platform) {
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

bool CollisionDetector::isGameObjectOnTopOfPlatform(std::unique_ptr<GameObject> gameObject, std::unique_ptr<Platform> platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, std::move(platform))) { // ERROR
        return true;
    }

	if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, std::move(platform))) { // ERROR
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(std::unique_ptr<GameObject> gameObject, std::unique_ptr<Platform> platform) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;
    int xPositionBottomLeftCorner = gameObject->xpos;
    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, std::move(platform))) { // ERROR
        return true;
    }

    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, std::move(platform))) { // ERROR
        return true;
    }

    return false;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(std::unique_ptr<GameObject> gameObject, std::unique_ptr<PlatformHolder> platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectOnTopOfPlatform(std::move(gameObject), std::move(platformHolder->platforms[i]))) { // ERROR, ERROR
            return true;
        }
    }
    return false;
}