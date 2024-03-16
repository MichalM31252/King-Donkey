extern "C" {
#include "./LadderHolder.h"
}

void initLadderHolder(LadderHolder* ladderHolder) {
	ladderHolder->ladders = new GameObject[MAXIMUM_AMOUNT_OF_LADDERS]; // this is the reason why platforms are not pointers
	ladderHolder->numberOfElements = 0; // number of elements currently inside
	ladderHolder->sizeOfArray = MAXIMUM_AMOUNT_OF_PLATFORMS;
}

void addLadder(LadderHolder* ladderHolder, GameObject* ladder) { // this doesn't work
	if (ladderHolder->numberOfElements == ladderHolder->sizeOfArray) {
		GameObject* temp = new GameObject[ladderHolder->sizeOfArray];

		for (int i = 0; i < ladderHolder->numberOfElements; i++) {
			temp[i] = ladderHolder->ladders[i];
		}

		delete[] ladderHolder->ladders;

		ladderHolder->ladders = temp;
		ladderHolder->sizeOfArray *= 2;
	}
	ladderHolder->ladders[ladderHolder->numberOfElements] = *ladder;
	ladderHolder->numberOfElements++;
}

void emptyLadderHolder(LadderHolder* ladderHolder) {
	delete[] ladderHolder->ladders;
}