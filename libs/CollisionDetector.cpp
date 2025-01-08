#include "CollisionDetector.h"
#include <iostream> // TEMP REMOVE AFTER TESTING

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

// Platform
//////////////////////////////////////////////////////////////////////////

struct Point {
    double x, y;
};

Point calculateCenter(const Point& v1, const Point& v2, const Point& v3, const Point& v4) {
    double centerX = (v1.x + v2.x + v3.x + v4.x) / 4.0;
    double centerY = (v1.y + v2.y + v3.y + v4.y) / 4.0;
    return { centerX, centerY };
}

Point rotatePoint(const Point& point, const Point& center, double angleDegrees) {
    double angleRadians = angleDegrees * M_PI / 180.0; // Convert degrees to radians
    double cosTheta = cos(angleRadians);
    double sinTheta = sin(angleRadians);

    // Translate point to origin
    double translatedX = point.x - center.x;
    double translatedY = point.y - center.y;

    // Rotate the point
    double rotatedX = translatedX * cosTheta - translatedY * sinTheta;
    double rotatedY = translatedX * sinTheta + translatedY * cosTheta;

    // Translate back to center
    return { rotatedX + center.x, rotatedY + center.y };
}

void rotateRectangle(Point vertices[], double angleDegrees) {
    // Calculate the center before rotation
    Point center = calculateCenter(vertices[0], vertices[1], vertices[2], vertices[3]);

    // Rotate each vertex
    for (int i = 0; i < 4; ++i) {
        vertices[i] = rotatePoint(vertices[i], center, angleDegrees);
    }
}

// Helper function to compute the cross product of vectors AB and AP
double crossProduct(const Point& A, const Point& B, const Point& P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

// Function to check if a point is inside the rectangle
bool isPointInsideRectangle(Point vertices[], const Point& point) {
    // Check the cross product for each edge
    for (int i = 0; i < 4; ++i) {
        Point A = vertices[i];
        Point B = vertices[(i + 1) % 4]; // Next vertex (loop back to 0 after the last vertex)
        if (crossProduct(A, B, point) < 0) {
            return false; // Point is outside for this edge
        }
    }
    return true; // Point is inside for all edges
}

bool CollisionDetector::isPointInsidePlatform(double x, double y, std::shared_ptr<Platform>& platform) {
	// Get the vertices of the platform
	Point vertices[4] = {
		{ platform->rect.x, platform->rect.y },
		{ platform->rect.x + platform->rect.w, platform->rect.y },
		{ platform->rect.x + platform->rect.w, platform->rect.y + platform->rect.h },
		{ platform->rect.x, platform->rect.y + platform->rect.h }
	};

	// HUGE BOTTLENECK, you are doing this every frame for no reason
	if (platform->angle != 0) {
		rotateRectangle(vertices, platform->angle);
	}

	// Check if the point is inside the rectangle
    return isPointInsideRectangle(vertices, { x, y });
}

bool CollisionDetector::isGameObjectInsideAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
    for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
        if (isGameObjectInsidePlatform(gameObject, platformHolder->platforms[i])) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
	for (int i = 0; i < platformHolder->getNumberOfElements(); i++) {
		if (isGameObjectOnTopOfPlatform(gameObject, platformHolder->platforms[i])) {
			return true;
		}
	}
	return false;
}

bool CollisionDetector::isGameObjectOnTopOfPlatform(const std::shared_ptr<const GameObject>& gameObject, std::shared_ptr<Platform> platform) {
	if (isPointInsidePlatform(gameObject->xpos, gameObject->ypos + gameObject->destRect.h + 1, platform)) {
		if (isPointInsidePlatform(gameObject->xpos + gameObject->destRect.w, gameObject->ypos + gameObject->destRect.h + 1, platform)) {
			return true;
		}
	}
    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>&gameObject, std::shared_ptr<Platform> platform) {
    for (int i = 0; i < 4; i++) {
		int x = gameObject->xpos + (i % 2) * gameObject->destRect.w;
		int y = gameObject->ypos + (i / 2) * gameObject->destRect.h;
        if (isPointInsidePlatform(x, y, platform)) {
            return true;
        }
    }
    return false;
}

// Ladder
//////////////////////////////////////////////////////////////////////////

bool CollisionDetector::isGameObjectInsideAnyLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const LadderContainer>& ladderContainer) {
    for (int i = 0; i < ladderContainer->getNumberOfElements(); i++) {
        if (isGameObjectInsideLadder(gameObject, ladderContainer->ladders[i])) {
            return true;
        }
    }
    return false;
}

bool CollisionDetector::isGameObjectInsideLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return isGameObjectWithinWidthOfLadder(gameObject, ladder) && isCollisionBetweenRects(gameObject->destRect, ladder->destRect);
}

bool CollisionDetector::isGameObjectWithinWidthOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return gameObject->xpos >= ladder->xpos && gameObject->xpos + gameObject->destRect.w < ladder->xpos + ladder->destRect.w;
}