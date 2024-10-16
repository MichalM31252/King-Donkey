#include "Platform.h"

void Platform::setPosition(int x1, int y1, int x2, int y2) {
	x1pos = x1;
	y1pos = y1;
	x2pos = x2;
	y2pos = y2;
}

// MOVE THIS TO SCREENMANAGER

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Platform::render(SDL_Surface* screen) const {
	int length = sqrt(pow(x2pos - x1pos, 2) + pow(y2pos - y1pos, 2));
	if (y1pos != y2pos) { // xdddddddddddddddddd
		int differenceBetweenX = sqrt(pow(x2pos - x1pos, 2));
		int x = x1pos;
		int y = y1pos;
		if (y1pos > y2pos) {
			for (int i = 0; i < differenceBetweenX; i++) {
				drawPixel(screen, x, y, 0xffffffff);
				x++;
				y--;
			}
		}
		if (y1pos < y2pos) {
			for (int i = 0; i < differenceBetweenX; i++) {
				drawPixel(screen, x, y, 0xffffffff);
				x++;
				y++;
			}
		}

	}
	else {
		drawLine(screen, x1pos, y1pos, length, 1, 0, 0xffffffff);
	}
}

// i dont think these should be here
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Platform::drawPixel(SDL_Surface* surface, int x, int y, Uint32 color)  const {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
}

void Platform::drawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) const {
	for (int i = 0; i < l; i++) {
		drawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

