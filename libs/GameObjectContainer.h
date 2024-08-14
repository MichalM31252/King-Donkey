#pragma once
#include "BarrelFactory.h" // no screen manager
#include "LadderHolder.h" // no screen manager
#include "PlatformHolder.h" // no screen manager
#include "MovableGameObject.h" // has screen manager
#include "Player.h" // no screen manager

struct GameObjectContainer {
	std::unique_ptr<GameObject> donkeyKong;
	std::unique_ptr<GameObject> princess;
	std::unique_ptr<Player> player;
	std::unique_ptr<PlatformHolder> platformHolder;
	std::unique_ptr<LadderHolder> ladderHolder;
	BarrelFactory* barrelFactory;
};
