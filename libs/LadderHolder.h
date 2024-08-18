#pragma once

extern "C" {
#include "GameObject.h"
#include "Constants.h"
}

extern "C++" {
#include <vector>
}

class LadderHolder {
public:
    std::vector<GameObject*> ladders;
    LadderHolder();
    void addLadder(GameObject* ladder);
    size_t getNumberOfElements() const;
};