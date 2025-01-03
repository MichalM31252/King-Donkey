#pragma once
#include "Platform.h"
#include "PlatformContainer.h"
#include "LadderContainer.h"

class CollisionDetector {
public:
    static bool isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b);

    static bool isPointInsidePlatform(int x, int y, std::shared_ptr<Platform>& platform);
    static bool isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, std::shared_ptr<Platform>& platform);
    static bool isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder);

    static bool isGameObjectInsideAnyLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const LadderContainer>& ladderContainer);
    static bool isGameObjectInsideLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);
    static bool isGameObjectWithinWidthOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);
    static bool isGameObjectWithinHeightOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);
};
