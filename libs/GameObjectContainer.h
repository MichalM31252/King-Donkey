#pragma once
#include "BarrelFactory.h"
#include "LadderHolder.h"
#include "PlatformHolder.h"
#include "MovableGameObject.h"
#include "Player.h"

struct GameObjectContainer {
    GameObject* donkeyKong;
    GameObject* princess;
    Player* player;
    PlatformHolder* platformHolder;
    LadderHolder* ladderHolder;
	BarrelHolder* barrelHolder;



    BarrelFactory* barrelFactory;
};
