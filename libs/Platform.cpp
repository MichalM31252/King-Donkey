#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include "./Platform.h"
#include "./Constants.h"
// rename 

void Platform::setPosition(int x1, int y1, int x2, int y2) {
	x1pos = x1;
	y1pos = y1;
	x2pos = x2;
	y2pos = y2;
}

void Platform::render(SDL_Surface* screen) {
	DrawPixel(screen, x1pos, y1pos, 0xffffffff);
	DrawPixel(screen, x2pos, y2pos, 0xffffffff);
}

void Platform::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

