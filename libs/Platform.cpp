#include "Platform.h"

// Constructor
Platform::Platform(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int width, int height, double angle)
    : renderer(renderer)
    , texture(texture)
    , angle(angle) 
{
    rect = { x, y, width, height };
}


// Render the platform
void Platform::render() {
    // Render the platform with tilt
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

bool Platform::isColliding(int objX, int objY, int objWidth, int objHeight) {
    // Calculate slope and intercept of the tilted platform's surface
    double radians = angle * M_PI / 180.0;
    double slope = std::tan(radians);
    double yIntercept = rect.y - slope * rect.x;

    // Check each corner of the object's bounding box
    int objBottom = objY + objHeight; // Bottom side of the bounding box
    int objRight = objX + objWidth;  // Right side of the bounding box

    // Check for collision with the platform's surface
    for (int cornerX : {objX, objRight}) {        // Left and right edges of the bounding box
        for (int cornerY : {objY, objBottom}) {   // Top and bottom edges of the bounding box
            double platformY = slope * cornerX + yIntercept;

            // Check if the corner is on or below the platform
            if (cornerY >= platformY && cornerY <= platformY + 5) {
                return true; // Collision detected
            }
        }
    }

    return false; // No collision
}

