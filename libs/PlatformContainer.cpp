#include "PlatformContainer.h"

PlatformContainer::PlatformContainer() = default;

void PlatformContainer::addPlatform(std::shared_ptr<Platform> platform) {
    platforms.push_back(platform);
}

size_t PlatformContainer::getNumberOfElements() const {
    return platforms.size();
}