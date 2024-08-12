extern "C" {
#include "LadderHolder.h"
}

void initLadderHolder(std::unique_ptr<LadderHolder>& ladderHolder) {
	ladderHolder->ladders = std::make_unique<GameObject[]>(MAXIMUM_AMOUNT_OF_LADDERS);
	ladderHolder->numberOfElements = 0;
	ladderHolder->sizeOfArray = MAXIMUM_AMOUNT_OF_PLATFORMS;
}

void addLadder(std::unique_ptr<LadderHolder>& ladderHolder, std::unique_ptr<GameObject>& ladder) {
    if (ladderHolder->numberOfElements == ladderHolder->sizeOfArray) {
        auto temp = std::make_unique<GameObject[]>(ladderHolder->sizeOfArray * 2);

        for (int i = 0; i < ladderHolder->numberOfElements; i++) {
            temp[i] = std::move(ladderHolder->ladders[i]);
        }

        ladderHolder->ladders = std::move(temp);
        ladderHolder->sizeOfArray *= 2;
    }
    ladderHolder->ladders[ladderHolder->numberOfElements] = std::move(*ladder);
    ladderHolder->numberOfElements++;
}

void emptyLadderHolder(std::unique_ptr<LadderHolder>& ladderHolder) {
    ladderHolder->ladders.reset();
    ladderHolder->numberOfElements = 0;
    ladderHolder->sizeOfArray = 0;
}