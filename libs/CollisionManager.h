#pragma once
extern "C" {
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../SDL2-2.0.10/include/SDL.h"
#include "../../SDL2-2.0.10/include/SDL_main.h"

#include "../Platform.h"
#include "../game_objects/GameObject.h"
#include "../game_objects/dynamic_game_objects/DynamicGameObject.h"
}

class CollisionManager {
public:
	bool isColliding = false;
	static bool isCollisionBetweenRects(SDL_Rect a, SDL_Rect b);
	static bool isDynamicGameObjectCollidingWithPlatform(DynamicGameObject* dynamicGameObject, Platform* platform);
	static bool isPointAPartOfLine(const int x, const int y, Platform* platform);
	static bool isRectInsideLadder(SDL_Rect a, SDL_Rect b);
};