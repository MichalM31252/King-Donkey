#pragma once

#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include <initializer_list>
#include <cmath>

class Platform {
private:
    SDL_Texture* texture;      // Texture for the platform
    SDL_Rect rect;             // Position and size of the platform
    double angle;              // Tilt angle in degrees
    SDL_Renderer* renderer;    // Renderer for drawing the platform

public:
    // Constructor
    Platform(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height, double angle);

    // Render the platform
    void render();

    // Collision detection
    bool isColliding(int objX, int objY, int objWidth, int objHeight);

    // Getters
    SDL_Rect getRect() const { return rect; }
    double getAngle() const { return angle; }
};
