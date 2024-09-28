#pragma once
#include "LadderContainer.h"
#include "PlatformContainer.h"
#include "MovableGameObject.h"
#include "Player.h"
#include "Gorilla.h"

struct GameObjectContainer {
    Gorilla* donkeyKong;
    GameObject* princess;
    Player* player;
    PlatformContainer* platformContainer;
    LadderContainer* ladderContainer;
	BarrelContainer* barrelContainer;
};
