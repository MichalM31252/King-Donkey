#pragma once

#include "GameObjectContainer.h"
#include <memory>

class AnimationManager {
public:
    std::shared_ptr<GameObjectContainer> gameObjectContainer;

    AnimationManager() = default;
    explicit AnimationManager(std::shared_ptr<GameObjectContainer> gameObjectContainer);

    void handleAnimations();

private:
    void handlePlayerAnimation();
    void handleAllBarrelsAnimation() const;
};