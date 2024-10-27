#pragma once
#include "LadderContainer.h"
#include "PlatformContainer.h"
#include "MovableGameObject.h"
#include "Player.h"
#include "Gorilla.h"

struct GameObjectContainer {
    std::shared_ptr<Gorilla> donkeyKong;
    std::shared_ptr<GameObject> princess;
    std::shared_ptr<Player> player;
    std::shared_ptr<PlatformContainer> platformContainer;
    std::shared_ptr<LadderContainer> ladderContainer;
    std::shared_ptr<BarrelContainer> barrelContainer;
};
