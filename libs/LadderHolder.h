#pragma once

extern "C" {
#include "GameObject.h"
#include "Constants.h"
}

struct LadderHolder {
	GameObject* ladders;
	int numberOfElements;
	int sizeOfArray;
};

void initLadderHolder(LadderHolder* ladderHolder);
void addLadder(LadderHolder* ladderHolder, GameObject* ladder);
void emptyLadderHolder(LadderHolder* ladderHolder);