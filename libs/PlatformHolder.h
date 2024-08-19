 #pragma once

#include "Platform.h"
#include "Constants.h"

extern "C++" {
#include <vector>
}

class PlatformHolder {
public:
    std::vector<Platform*> platforms;
    PlatformHolder();
    void addPlatform(Platform* platform);
    size_t getNumberOfElements() const;
};


