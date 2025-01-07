#include "CollisionResolver.h"

CollisionResolver::CollisionResolver()
    : gameObjectContainer(std::make_shared<GameObjectContainer>())
{
}

CollisionResolver::CollisionResolver(std::shared_ptr<GameObjectContainer> gameObjectContainer)
    : gameObjectContainer(gameObjectContainer)
{
}



// CREATE ONE BIGGER FUNCTION NOT JUST FOR PLAYER



// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
void CollisionResolver::handlePlayerCollisionWithKong() const {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->donkeyKong->destRect)) {
        closeGame();
    }
}

// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
void CollisionResolver::handlePlayerCollisionWithPrincess() const {
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, gameObjectContainer->princess->destRect)) {
        closeGame();
    }
}

// REFACTOR THIS TO handleCollisionWIthBarrel and based on the parameters given handle the function
// don't care which object is the first or the second
// name the arguments gameObject1 and gameObject2
void CollisionResolver::handlePlayerCollisionWithBarrel(std::shared_ptr<Barrel> barrel, GameState* gameState) const{
    if (CollisionDetector::isCollisionBetweenRects(gameObjectContainer->player->destRect, barrel->destRect)) {
		*gameState = GameState::GAME_OVER;
    }
}

void CollisionResolver::handleCollisionWithJumping() {
    if (gameObjectContainer->player->isFalling) {
        gameObjectContainer->player->stopFalling();
        gameObjectContainer->player->checkIfJumpPossible = false;
    }
    if (!gameObjectContainer->player->isFalling && gameObjectContainer->player->checkIfJumpPossible) {
        gameObjectContainer->player->startJumping();
        gameObjectContainer->player->checkIfJumpPossible = false;
    }
}

struct PointSecond {
    double x, y;
};

PointSecond calculateCenter(const PointSecond& v1, const PointSecond& v2, const PointSecond& v3, const PointSecond& v4) {
    double centerX = (v1.x + v2.x + v3.x + v4.x) / 4.0;
    double centerY = (v1.y + v2.y + v3.y + v4.y) / 4.0;
    return { centerX, centerY };
}

PointSecond rotatePoint(const PointSecond& point, const PointSecond& center, double angleDegrees) {
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

void rotateRectangle(PointSecond vertices[], double angleDegrees) {
    // Calculate the center before rotation
    PointSecond center = calculateCenter(vertices[0], vertices[1], vertices[2], vertices[3]);

    // Rotate each vertex
    for (int i = 0; i < 4; ++i) {
        vertices[i] = rotatePoint(vertices[i], center, angleDegrees);
    }
}

// TEMPORARY FIX
void CollisionResolver::handleCollisionWithPlatform(const std::shared_ptr<MovableGameObject>& gameObject) {
    int yPosition = gameObject->ypos + gameObject->destRect.h;

    for (int i = 0; i < gameObjectContainer->platformContainer->getNumberOfElements(); i++) {
        if (CollisionDetector::isGameObjectInsidePlatform(gameObject, gameObjectContainer->platformContainer->platforms[i])) {

            if (gameObject->isFalling) {
                gameObject->stopFalling();
            }

            auto platform = gameObjectContainer->platformContainer->platforms[i];

            if (platform->angle != 0) {
                PointSecond vertices[4] = {
                    { platform->rect.x, platform->rect.y },
                    { platform->rect.x + platform->rect.w, platform->rect.y },
                    { platform->rect.x + platform->rect.w, platform->rect.y + platform->rect.h },
                    { platform->rect.x, platform->rect.y + platform->rect.h }
                };
                rotateRectangle(vertices, platform->angle);

                int smallestYAtX = INT_MAX; // Initialize to a very large value

                // Check only the bottom-left and bottom-right corners of the object
                int xPositions[2] = {
                    gameObject->xpos, // Bottom-left corner
                    gameObject->xpos + gameObject->destRect.w // Bottom-right corner
                };

                for (int j = 0; j < 2; j++) {
                    int x = xPositions[j];
                    int y = gameObject->ypos + gameObject->destRect.h; // Bottom corner's Y position

                    if (CollisionDetector::isPointInsidePlatform(x, y, platform)) {
                        // Move upwards to find the platform surface
                        while (CollisionDetector::isPointInsidePlatform(x, y, platform)) {
                            y--;
                        }
                        if (y < smallestYAtX) {
                            smallestYAtX = y;
                        }
                    }
                }

                if (smallestYAtX != INT_MAX) {
                    gameObject->ypos = smallestYAtX - gameObject->destRect.h; // Adjust the player's Y position
                }
            }
        }
    }
}


void CollisionResolver::handlePlayerCollision() {
    auto player = gameObjectContainer->player;

    handleCollisionWithPlatform(player);
    // refactor this to handleCollisionWithKong() and based on the type of the given object handle the function
    handlePlayerCollisionWithKong();
	// refactor this to handleCollisionWithPrincess() and based on the type of the given object handle the function
    handlePlayerCollisionWithPrincess();

    // HANDLE JUMPING MECHANISM WAS HERE FOR SOME REASON
    // handlePlayerJumping();
}

void CollisionResolver::handleBarrelsCollision(GameState* gameState) {

}


[[noreturn]] void CollisionResolver::closeGame() const {
    SDL_Quit();
    exit(0);
}