extern "C" {
#include "LadderHolder.h"
}

LadderHolder::LadderHolder() = default;

void LadderHolder::addLadder(GameObject* ladder) {
    ladders.push_back(ladder);
}

size_t LadderHolder::getNumberOfElements() const {
    return ladders.size();
}