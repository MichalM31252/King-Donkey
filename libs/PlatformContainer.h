 #pragma once

#include "Platform.h"
#include "Constants.h"
#include <vector>

class PlatformContainer {
public:
    std::vector<Platform*> platforms;
    PlatformContainer();
    void addPlatform(Platform* platform);
    size_t getNumberOfElements() const;
};


