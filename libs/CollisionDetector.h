#pragma once
#include "MovableGameObject.h"
#include "Platform.h"
#include "PlatformContainer.h"
#include "LadderContainer.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

// tracks every game object in the game and checks if they collide

class CollisionDetector
{
public:
    static bool isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b);
	static bool isXWithinWidthOfPlatform(const int x, const Platform* platform);
    static bool isPointAPartOfLine(const int x, const int y, const Platform* platform);

    static bool isGameObjectOnTopOfPlatform(const GameObject* gameObject, const Platform* platform);
    static bool isGameObjectInsidePlatform(const GameObject* gameObject, const Platform* platform);
    static bool isGameObjectOnTopOfAnyPlatform(const GameObject* gameObject, const PlatformContainer* platformHolder);
	
    static bool isGameObjectInsideAnyLadder(const GameObject* gameObject, const LadderContainer* ladderContainer);
    static bool isGameObjectInsideLadder(const GameObject* gameObject, const GameObject* ladder);

    static bool isGameObjectWithinWidthOfLadder(const GameObject* gameObject, const GameObject* ladder);
    static bool isGameObjectWithinHeightOfLadder(const GameObject* gameObject, const GameObject* ladder);
	// isPlayerClimbingTheLadder (check if player is inside ladder, then check if if player is not touching the platform (ok but what about falling))
};