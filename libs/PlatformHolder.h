 #pragma once

extern "C" {
#include "Platform.h"
#include "Constants.h"
}

extern "C++" {
#include <memory>
#include <vector>
}

class PlatformHolder {
public:
    std::vector<std::unique_ptr<Platform>> platforms;
    PlatformHolder();
    void addPlatform(std::unique_ptr<Platform> platform);
    size_t getNumberOfElements() const;
};


