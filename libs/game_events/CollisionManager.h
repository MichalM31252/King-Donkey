#pragma once
extern "C" {
#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"
#include "../Platform.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/dynamic_game_objects/DynamicGameObject.h"
}

class CollisionManager {
public:
	bool isColliding = false;
	bool isCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	bool isDynamicGameObjectCollidingWithPlatform(DynamicGameObject* dynamicGameObject, Platform* platform);
	bool isRectInsideLadder(SDL_Rect a, SDL_Rect b);
};