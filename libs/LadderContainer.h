#pragma once

#include "GameObject.h"
#include "Constants.h"
#include <vector>
#include <memory>

class LadderContainer {
public:
    std::vector<std::shared_ptr<GameObject>> ladders;
    LadderContainer();
    void addLadder(std::shared_ptr<GameObject> ladder);
    size_t getNumberOfElements() const;
};