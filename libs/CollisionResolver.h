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
#include "CollisionDetector.h"
}

// Does something when objects collide

class CollisionResolver {
public:
	GameObjectContainer *gameObjectContainer;
	ScreenManager* screenManager;

	bool isColliding = false;

	CollisionResolver();
	CollisionResolver(GameObjectContainer* gameObjectContainer, ScreenManager* screenManager);

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