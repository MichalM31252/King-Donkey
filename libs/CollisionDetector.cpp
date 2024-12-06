#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

//bool CollisionDetector::isXWithinWidthOfPlatform(int x, const std::shared_ptr<const Platform>& platform) {
//    return (x >= platform->x1pos && x <= platform->x2pos) || (x <= platform->x1pos && x >= platform->x2pos);
//}

bool CollisionDetector::isXWithinWidthOfPlatform(int x, const std::shared_ptr<const Platform>& platform) {
    SDL_Rect platformRect = platform->getRect();
    return x >= platformRect.x && x <= platformRect.x + platformRect.w;
}

//bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
//    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
//        if (CollisionDetector::isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
//            return true;
//        }
//    }
//    return false;
//}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
            return true;
        }
    }
    return false;
}


//bool CollisionDetector::isGameObjectOnTopOfPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform) {
//    int yPosition = gameObject->ypos + gameObject->destRect.h;
//    int xPositionBottomLeftCorner = gameObject->xpos;
//    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;
//
//    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition + 1, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomRightCorner, platform)) {
//        return true;
//    }
//
//    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition + 1, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomLeftCorner, platform)) {
//        return true;
//    }
//
//    return false;
//}

bool CollisionDetector::isGameObjectOnTopOfPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform) {
    SDL_Rect gameObjectRect = gameObject->destRect; // The object's bounding box
    SDL_Rect platformRect = platform->getRect();

    // Calculate the bottom-center point of the GameObject
    int bottomCenterX = gameObjectRect.x + gameObjectRect.w / 2;
    int bottomY = gameObjectRect.y + gameObjectRect.h;

    // Check if the bottom-center point is on or near the platform
    return isPointAPartOfLine(bottomCenterX, bottomY, platform) &&
        isXWithinWidthOfPlatform(bottomCenterX, platform);
}


//bool CollisionDetector::isPointAPartOfLine(int x, int y, const std::shared_ptr<const Platform>& platform) {
//    double a = platform->y2pos - platform->y1pos;
//    double b = platform->x1pos - platform->x2pos;
//    double c = a * platform->x1pos + b * platform->y1pos;
//
//    return a * x + b * y == c;
//}

bool CollisionDetector::isPointAPartOfLine(int x, int y, const std::shared_ptr<const Platform>& platform) {
    // Calculate slope and y-intercept of the platform's line
    double radians = platform->getAngle() * M_PI / 180.0;
    double slope = std::tan(radians);
    double yIntercept = platform->getRect().y - slope * platform->getRect().x;

    // Check if the point (x, y) lies on the platform's line
    double expectedY = slope * x + yIntercept;
    return std::abs(y - expectedY) <= 1e-5; // Allow for small floating-point errors
}

//bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform) {
//    int yPosition = gameObject->ypos + gameObject->destRect.h;
//    int xPositionBottomLeftCorner = gameObject->xpos;
//    int xPositionBottomRightCorner = gameObject->xpos + gameObject->destRect.w;
//
//    if (CollisionDetector::isPointAPartOfLine(xPositionBottomLeftCorner, yPosition, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomLeftCorner, platform)) {
//        return true;
//    }
//
//    if (CollisionDetector::isPointAPartOfLine(xPositionBottomRightCorner, yPosition, platform) && CollisionDetector::isXWithinWidthOfPlatform(xPositionBottomRightCorner, platform) ) {
//        return true;
//    }
//
//    return false;
//}

bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform) {
    SDL_Rect gameObjectRect = gameObject->destRect;
    SDL_Rect platformRect = platform->getRect();

    // Check if the game object's bounding box intersects the platform's bounding box
    return SDL_HasIntersection(&gameObjectRect, &platformRect);
}


bool CollisionDetector::isGameObjectInsideAnyLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const LadderContainer>& ladderContainer) {
    for (int i = 0; i < ladderContainer->getNumberOfElements(); i++) {
        if (isGameObjectInsideLadder(gameObject, ladderContainer->ladders[i])) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectInsideLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return isGameObjectWithinWidthOfLadder(gameObject, ladder) && isCollisionBetweenRects(gameObject->destRect, ladder->destRect);
}

bool CollisionDetector::isGameObjectWithinWidthOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return gameObject->xpos >= ladder->xpos && gameObject->xpos + gameObject->destRect.w < ladder->xpos + ladder->destRect.w;
}

bool CollisionDetector::isGameObjectWithinHeightOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return gameObject->ypos >= ladder->ypos && gameObject->ypos <= ladder->ypos + ladder->destRect.h;
}