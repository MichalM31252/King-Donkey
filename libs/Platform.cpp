#include "Platform.h"

// Constructor
Platform::Platform(int x, int y, int width, int height, double angle)
    : angle(angle) 
{
    rect = { x, y, width, height };
}

// THE PROBLEM WITH COLLISION IS HERE?
bool Platform::isColliding(int objX, int objY, int objWidth, int objHeight) {
	int x1 = objX;
	int y1 = objY;

	int x2 = objX + objWidth;
	int y2 = objY;

	int x3 = objX;
	int y3 = objY + objHeight;

	int x4 = objX + objWidth;
	int y4 = objY + objHeight;

    if (isPointInsidePlatform(x1, y1) || isPointInsidePlatform(x2, y2) || isPointInsidePlatform(x3, y4) || isPointInsidePlatform(x4, y4)) {
        return true;
    }
    return false;
}

bool Platform::isPointInsidePlatform(float px, float py) {
    float radians = angle * M_PI / 180.0f;
    float dx = std::cos(radians) * rect.w;
    float dy = std::sin(radians) * rect.w;

    // Equation of the line formed by the top edge of the platform
    float slope = dy / dx;
    float intercept = rect.y - slope * rect.x;

    // Check if the point lies on the top edge within the platform's bounds
    return px >= rect.x && px <= rect.x + dx && py >= slope * px + intercept && py <= slope * px + intercept + rect.h;
}

