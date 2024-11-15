#pragma once
#include "Platform.h"
#include "PlatformContainer.h"
#include "LadderContainer.h"

// tracks every game object in the game and checks if they collide

class CollisionDetector
{
public:
    static bool isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b);
    static bool isXWithinWidthOfPlatform(int x, const std::shared_ptr<const Platform>& platform);
    static bool isPointAPartOfLine(int x, int y, const std::shared_ptr<const Platform>& platform);

    static bool isGameObjectOnTopOfPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform);
    static bool isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const Platform>& platform);
    static bool isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder);

    static bool isGameObjectInsideAnyLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const LadderContainer>& ladderContainer);
    static bool isGameObjectInsideLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);

    static bool isGameObjectWithinWidthOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);
    static bool isGameObjectWithinHeightOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder);
	// isPlayerClimbingTheLadder (check if player is inside ladder, then check if if player is not touching the platform (ok but what about falling))
};