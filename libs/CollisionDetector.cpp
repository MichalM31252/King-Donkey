#include "CollisionDetector.h"
#include <iostream> // TEMP REMOVE AFTER TESTING

bool CollisionDetector::isCollisionBetweenRects(const SDL_Rect a, const SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

// Platform
//////////////////////////////////////////////////////////////////////////

bool CollisionDetector::isGameObjectOnTopOfAnyPlatform(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const PlatformContainer>& platformHolder) {
		// TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING
	// TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING
	// TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING

	auto normalPlatform = platformHolder->platforms[0];
	if (isPointInsidePlatform(100, 404, normalPlatform)) { // should be true
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}

	if (isPointInsidePlatform(500, 404, normalPlatform)) { // should be false
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}

	if (isPointInsidePlatform(200, 390, normalPlatform)) { // should be false
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}

	if (isPointInsidePlatform(201, 404, normalPlatform)) { // should be true
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}


	auto tiltedPlatform = platformHolder->platforms[1];
	if (isPointInsidePlatform(440, 360, tiltedPlatform)) { // should be false
        std::cout << "true" << std::endl;
	}
    else {
        std::cout << "false" << std::endl;
    }

	if (isPointInsidePlatform(420, 370, tiltedPlatform)) {// should be false
		std::cout << "true" << std::endl;
	}
	else {
		std::cout << "false" << std::endl;
	}

	if (isPointInsidePlatform(450, 354, tiltedPlatform)) { // should be true
		std::cout << "true" << std::endl;
	}
    else {
        std::cout << "false" << std::endl;
    }
    
    
    return false;
}

bool CollisionDetector::isGameObjectInsidePlatform(const std::shared_ptr<const GameObject>& gameObject, std::shared_ptr<Platform>& platform) {
	// First thing I thought about is to check if the rectangle of the gameObject is inside the rectangle of the platform
    // but this is not enough, when I'll implement a tilted platform it will not work
	// a platform has a starting x position, starting y position, height, width and a slope
	// there is no way to implement here the slope when using isCollisionBetweenRects method 
	// so I need to implement a new method that will check if the gameObject is inside the platform

    // The second thing is that, now a platform has height and width other than 1 pixel
	// which means that the player won't be able to pass throught it by accident like before
	// so I need to implement a mechanism that will check each point of the player's rectangle
	// THEN take in consideration the platforms height and width and slope and check if the player is inside the platform

	return false;
}

bool CollisionDetector::isPointInsidePlatform(int x, int y, std::shared_ptr<Platform>& platform) {
	// The values of x grow to the right and the values of y grow to the bottom
	int platformX = platform->rect.x;
	int platformY = platform->rect.y;
	int platformWidth = platform->rect.w;
	int platformHeight = platform->rect.h;
	double platformAngle = platform->angle; // the angle is always clockwise

    // Compute the center of the platform
    double centerX = platformX + platformWidth / 2.0;
    double centerY = platformY + platformHeight / 2.0;

    // Translate point to the platform's coordinate system (centered at the rectangle's center)
    double translatedX = x - centerX;
    double translatedY = y - centerY;

    // Rotate the point counterclockwise by the platform's angle to "unrotate" it
    double cosTheta = cos(-platformAngle);
    double sinTheta = sin(-platformAngle);
    double unrotatedX = translatedX * cosTheta - translatedY * sinTheta;
    double unrotatedY = translatedX * sinTheta + translatedY * cosTheta;

    // Check if the unrotated point lies within the bounds of the axis-aligned rectangle
    double halfWidth = platformWidth / 2.0;
    double halfHeight = platformHeight / 2.0;

    return (unrotatedX >= -halfWidth && unrotatedX <= halfWidth && unrotatedY >= -halfHeight && unrotatedY <= halfHeight);
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

bool CollisionDetector::isGameObjectWithinHeightOfLadder(const std::shared_ptr<const GameObject>& gameObject, const std::shared_ptr<const GameObject>& ladder) {
    return gameObject->ypos >= ladder->ypos && gameObject->ypos <= ladder->ypos + ladder->destRect.h;
}