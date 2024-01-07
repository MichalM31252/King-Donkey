#pragma once

extern "C" {
#include "./Platform.h"
}


struct PlatformHolder {
	Platform* platforms;
	int numberOfElements;
	int sizeOfArray;
};

void init(PlatformHolder* platformHolder);
void addPlatform(PlatformHolder* platformHolder, Platform* platform);
void emptyPlatformHolder(PlatformHolder* platformHolder);

// void addEveryPlatform(); // do this when reading from a file


