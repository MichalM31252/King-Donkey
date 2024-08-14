extern "C" {
#include "LadderHolder.h"
}

LadderHolder::LadderHolder() = default;

void LadderHolder::addLadder(std::unique_ptr<GameObject>& ladder) {
	ladders.push_back(std::move(ladder));
}

size_t LadderHolder::getNumberOfElements() const {
	return ladders.size();
}