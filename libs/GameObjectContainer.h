#pragma once

#include "BarrelDispenser.h"
#include "LadderHolder.h"
#include "PlatformHolder.h"
#include "DynamicGameObject.h"
#include "Player.h"

// turn this into a struct in the future

struct GameObjectContainer {
    GameObject* donkeyKong;
    GameObject* princess;
    Player* player;
    PlatformHolder* platformHolder;
    LadderHolder* ladderHolder;
    BarrelDispenser* barrelDispenser;
};
