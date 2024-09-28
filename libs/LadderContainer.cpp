#include "LadderContainer.h"

LadderContainer::LadderContainer() = default;

void LadderContainer::addLadder(GameObject* ladder) {
    ladders.push_back(ladder);
}

size_t LadderContainer::getNumberOfElements() const {
    return ladders.size();
}