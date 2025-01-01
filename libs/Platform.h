#pragma once

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include <initializer_list>
#include <cmath>

class Platform {
public:
    SDL_Rect rect;             // Position and size of the platform
    double angle;              // Tilt angle in degrees
    SDL_Surface* surface;       // the image of the game object

    // Constructor
    Platform(int x, int y, int width, int height, double angle);

    // Collision detection
    bool isColliding(int objX, int objY, int objWidth, int objHeight);
	bool isPointInsidePlatform(float px, float py);
};
