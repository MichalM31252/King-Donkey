#include "CollisionDetector.h"

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

// Platform
//////////////////////////////////////////////////////////////////////////

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
    SDL_Rect gameObjectRect = gameObject->destRect;

    // Iterate through all platforms and check for collision
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (platformHolder->platforms[i]->isColliding(gameObjectRect.x, gameObjectRect.y, gameObjectRect.w, gameObjectRect.h)) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, std::shared_ptr<Platform>& platform) {
    SDL_Rect gameObjectRect = gameObject->destRect;
    SDL_Rect platformRect = platform->rect;

    // Check if the game object's bounding box intersects the platform's bounding box
	return platform->isColliding(gameObjectRect.x, gameObjectRect.y, gameObjectRect.w, gameObjectRect.h);
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