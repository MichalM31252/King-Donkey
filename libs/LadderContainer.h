#pragma once

#include "GameObject.h"
#include "Constants.h"
#include <vector>

class LadderContainer {
public:
    std::vector<GameObject*> ladders;
    LadderContainer();
    void addLadder(GameObject* ladder);
    size_t getNumberOfElements() const;
};