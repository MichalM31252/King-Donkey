#include "PlatformHolder.h"

PlatformHolder::PlatformHolder() = default;

void PlatformHolder::addPlatform(Platform* platform) {
    platforms.push_back(platform);
}

size_t PlatformHolder::getNumberOfElements() const {
    return platforms.size();
}