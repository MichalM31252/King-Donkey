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
}

class CollisionManager {
public:
	GameObjectContainer *gameObjectContainer;
	bool isColliding = false;

	CollisionManager();
	CollisionManager(GameObjectContainer* gameObjectContainer);
	
	static bool isCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	static bool isDynamicGameObjectCollidingWithPlatform(DynamicGameObject* dynamicGameObject, Platform* platform);
	static bool isPointAPartOfLine(const int x, const int y, Platform* platform);
	static bool isRectInsideLadder(SDL_Rect a, SDL_Rect b);

	// Game object manager or collision manager?
	/////////////////////////////////////////////////////////////////////////////////////

	void handleCollisionWithKong();
	void handleCollisionWithPrincess();
	void handleCollisionWithBarrel(DynamicGameObject* barrel, bool* quit, int* startAnotherRound);
	void handleCollisionWithLadder(int* flagLadder);
	void handleCollisionWithPlatform(DynamicGameObject* gameObject, int* flagPlatform);
	void handleCollisionWithJumping();

	/////////////////////////////////////////////////////////////////////////////////////


	void closeGame();
};