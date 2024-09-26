#pragma once
#include "BarrelFactory.h"
#include "LadderHolder.h"
#include "PlatformHolder.h"
#include "MovableGameObject.h"
#include "Player.h"
#include "Gorilla.h"

// rename holder to container

struct GameObjectContainer {
    Gorilla* donkeyKong;
    GameObject* princess;
    Player* player;
    PlatformHolder* platformHolder;
    LadderHolder* ladderHolder;
	BarrelHolder* barrelHolder;
};
