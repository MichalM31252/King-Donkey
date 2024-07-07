#pragma once
#include "BarrelDispenser.h" // no screen manager
#include "LadderHolder.h" // no screen manager
#include "PlatformHolder.h" // no screen manager
#include "DynamicGameObject.h" // has screen manager
#include "Player.h" // no screen manager

struct GameObjectContainer {
    GameObject* donkeyKong;
    GameObject* princess;
    Player* player;
    PlatformHolder* platformHolder;
    LadderHolder* ladderHolder;
    BarrelDispenser* barrelDispenser;
};
