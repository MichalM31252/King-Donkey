extern "C" {
#include "PlatformHolder.h"
}

PlatformHolder::PlatformHolder() = default;

void PlatformHolder::addPlatform(std::unique_ptr<Platform> platform) {
    platforms.push_back(std::move(platform));
}

size_t PlatformHolder::getNumberOfElements() const {
    return platforms.size();
}