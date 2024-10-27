 #pragma once

#include "Platform.h"
#include "Constants.h"
#include <vector>
#include <memory>

class PlatformContainer {
public:
    std::vector<std::shared_ptr<Platform>> platforms;
    PlatformContainer();
    void addPlatform(std::shared_ptr<Platform> platform);
    size_t getNumberOfElements() const;
};


