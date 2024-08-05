#pragma once
extern "C" {
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "MovableGameObject.h"
#include "Platform.h"

}
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
	static bool isCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	static bool isPointAPartOfLine(const int x, const int y, Platform* platform);
	static bool isRectInsideLadder(SDL_Rect a, SDL_Rect b);

	static bool isGameObjectOnTopOfPlatform(GameObject* gameObject, Platform* platform);
	static bool isGameObjectInsidePlatform(GameObject* gameObject, Platform* platform);
	// isGameObjectInsideBarrel

	// isPlayerClimbingTheLadder (check if player is inside ladder, then check if if player is not touching the platform (ok but what about falling))
};