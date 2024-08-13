#pragma once
#include "BarrelFactory.h" // no screen manager
#include "LadderHolder.h" // no screen manager
#include "PlatformHolder.h" // no screen manager
#include "MovableGameObject.h" // has screen manager
#include "Player.h" // no screen manager

struct GameObjectContainer {
	GameObject* donkeyKong;
	GameObject* princess;
	std::unique_ptr<Player> player;
	PlatformHolder* platformHolder;
	LadderHolder* ladderHolder;
	BarrelFactory* barrelFactory;
};
