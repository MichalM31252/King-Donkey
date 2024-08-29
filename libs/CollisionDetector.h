#pragma once
#include "MovableGameObject.h"
#include "Platform.h"
#include "PlatformHolder.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

// tracks every game object in the game and checks if they collide

// in the future merge most of these methods into one method that will check if two game objects collide
// once every game object has a hitbox

// is movable game object colliding with ladder
// is movable game object colliding with barrel
// is movable game object colliding with platform
// is movable game object colliding with kong
// is movable game object colliding with princess
// is movable game object colliding with the edge of the screen


// !!! is movable game object colliding with another movable game object !!!

class CollisionDetector
{
public:
    static bool isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b);
	static bool isPointWithinWidthOfPlatform(const int x, const int y, const Platform* platform);
    static bool isPointAPartOfLine(const int x, const int y, const Platform* platform);

    static bool isGameObjectOnTopOfPlatform(const GameObject* gameObject, const Platform* platform);
    static bool isGameObjectInsidePlatform(const GameObject* gameObject, const Platform* platform);
    static bool isGameObjectOnTopOfAnyPlatform(const GameObject* gameObject, const PlatformHolder* platformHolder);
	// isGameObjectInsideBarrel

	// isPlayerClimbingTheLadder (check if player is inside ladder, then check if if player is not touching the platform (ok but what about falling))
};