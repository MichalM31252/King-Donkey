#pragma once

extern "C" {
#include "GameObject.h"
#include "Constants.h"
}

extern "C++" {
#include <memory>
}

struct LadderHolder {
    std::unique_ptr<GameObject[]> ladders;
    int numberOfElements;
    int sizeOfArray;
};

void initLadderHolder(std::unique_ptr<LadderHolder>& ladderHolder);
void addLadder(std::unique_ptr<LadderHolder>& ladderHolder, std::unique_ptr<GameObject>& ladder);
void emptyLadderHolder(std::unique_ptr<LadderHolder>& ladderHolder);