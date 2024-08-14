#pragma once

extern "C" {
#include "GameObject.h"
#include "Constants.h"
}

extern "C++" {
#include <memory>
#include <vector>
}

class LadderHolder {
private:
    std::vector<std::unique_ptr<GameObject>> ladders;
public:
    LadderHolder();
    void addLadder(std::unique_ptr<GameObject>& ladder);
    size_t getNumberOfElements() const;
};