#pragma once

extern "C" {
#include "Platform.h"
#include "Constants.h"
}

struct PlatformHolder {
	Platform* platforms;
	int numberOfElements;
	int sizeOfArray;
};

void initPlatformHolder(PlatformHolder* platformHolder);
void addPlatform(PlatformHolder* platformHolder, Platform* platform);
void emptyPlatformHolder(PlatformHolder* platformHolder);


