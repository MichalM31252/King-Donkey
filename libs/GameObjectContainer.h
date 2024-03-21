#pragma once

#include "./BarrelDispenser.h" // // 
#include "./LadderHolder.h" // // // 
#include "./PlatformHolder.h" // // // //
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h" // // // //
#include "./game_objects/dynamic_game_objects/dynamic_game_object_child/Player.h" // // // // // //

class GameObjectContainer {
public:
	GameObject* donkeyKong;
	GameObject* princess;
	Player* player;
	PlatformHolder* platformHolder;
	LadderHolder* ladderHolder;
	BarrelDispenser* barrelDispenser;
};