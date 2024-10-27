#include "LadderContainer.h"

LadderContainer::LadderContainer() = default;

void LadderContainer::addLadder(std::shared_ptr<GameObject> ladder) {
    ladders.push_back(ladder);
}

size_t LadderContainer::getNumberOfElements() const {
    return ladders.size();
}