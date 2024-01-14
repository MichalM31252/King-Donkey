
extern "C" {
#include "./game_objects/dynamic_game_objects/DynamicGameObject.h"
#include "./BarrelHolder.h"
#include "./BarrelDispenser.h"
}

void BarrelDispenser::initBarrelDispenser(BarrelDispenser* barrelDispenser) {
	barrelDispenser->barrelHolder = new BarrelHolder;
	initBarrelHolder(barrelDispenser->barrelHolder);
}

void BarrelDispenser::setPosition(int x, int y) {
	xpos = x;
	ypos = y;
}

void BarrelDispenser::updateBarrelDispenser() {

}

void BarrelDispenser::throwBarrel() {

}