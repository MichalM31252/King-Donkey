#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

// Platform
//////////////////////////////////////////////////////////////////////////

bool CollisionDetector::isXWithinWidthOfPlatform(int x, const std::shared_ptr<const Platform>& platform) {
    SDL_Rect platformRect = platform->rect;
    return x >= platformRect.x && x <= platformRect.x + platformRect.w;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
    SDL_Rect gameObjectRect = gameObject->destRect;

    // Iterate through all platforms and check for collision
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (platformHolder->platforms[i]->isColliding(
            gameObjectRect.x,
            gameObjectRect.y,
            gameObjectRect.w,
            gameObjectRect.h)) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectOnTopOfPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<Platform>& platform) {
    SDL_Rect gameObjectRect = gameObject->destRect;

    // Use the platform's isColliding method directly
    return platform->isColliding(
        gameObjectRect.x,
        gameObjectRect.y,
        gameObjectRect.w,
        gameObjectRect.h);
}

///////////////

bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform) {
    SDL_Rect gameObjectRect = gameObject->destRect;
    SDL_Rect platformRect = platform->rect;

    // Check if the game object's bounding box intersects the platform's bounding box
    return SDL_HasIntersection(&gameObjectRect, &platformRect);
}








// Ladder
//////////////////////////////////////////////////////////////////////////

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