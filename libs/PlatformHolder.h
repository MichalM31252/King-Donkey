#pragma once

extern "C" {
	#include "./Platform.h"
}


struct PlatformHolder {
	int* platforms;
	int numberOfElements;
	int sizeOfHolder;
};

void initPlatformHolder();
void addPlatform();
void renderEveryPlatform();
// void addEveryPlatform(); // do this when reading from a file


