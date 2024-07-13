#pragma once
extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"

#include "Platform.h"
#include "GameObject.h"
#include "DynamicGameObject.h"
#include "GameObjectContainer.h"
#include "PhysicsManager.h"
#include "ScreenManager.h"
}

// Does something when objects collide

class CollisionResolver {
public:
	GameObjectContainer *gameObjectContainer;
	ScreenManager* screenManager;

	bool isColliding = false;

	CollisionResolver();
	CollisionResolver(GameObjectContainer* gameObjectContainer, ScreenManager* screenManager);
	
	static bool isCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	static bool isDynamicGameObjectCollidingWithPlatform(DynamicGameObject* dynamicGameObject, Platform* platform);
	static bool isPointAPartOfLine(const int x, const int y, Platform* platform);
	static bool isRectInsideLadder(SDL_Rect a, SDL_Rect b);

	// Game object manager or collision manager?
	/////////////////////////////////////////////////////////////////////////////////////

	void handlePlayerCollisionWithKong();
	void handlePlayerCollisionWithPrincess();
	void handlePlayerCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
	void handlePlayerCollisionWithLadder();
	void handleCollisionWithPlatform(DynamicGameObject* gameObject, int* isGameObjectInsidePlatform);
	void handleCollisionWithJumping();

	/////////////////////////////////////////////////////////////////////////////////////

	void handlePlayerCollision();
	void handleBarrelsCollision(bool* quit, int* startAnotherRound);

	void closeGame();
};