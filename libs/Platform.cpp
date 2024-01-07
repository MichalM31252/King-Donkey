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

	x3pos = x1pos;
	y3pos = y1pos - 1;
	x4pos = x2pos;
	y4pos = y2pos - 1;
}

void Platform::render(SDL_Surface* screen) {
	DrawPixel(screen, x1pos, y1pos, 0xffffffff);
	DrawPixel(screen, x2pos, y2pos, 0xffffffff);
	//DrawPixel(screen, x3pos, y3pos, 0xffffffff);
	//DrawPixel(screen, x4pos, y4pos, 0xffffffff);
}

void Platform::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Platform::setEquationLine() {
	a1 = y1pos - y2pos;
	b1 = x2pos - x1pos;
	c1 = (x1pos - x2pos) * y1pos + (y2pos - y1pos) * x1pos;

	a2 = y3pos - y4pos;
	b2 = x4pos - x3pos;
	c2 = (x3pos - x4pos) * y3pos + (y4pos - y3pos) * x3pos;

	// cout<<"("<<a<<"x) + ("<<b<<"y) + ("<<c<< = 0
	// The equation of line is (-5x) + (4y) + (11) = 0
	// ax + by + c = 0
	// I need y

	int x = 1;

	double y = ((-1.0 * a1 * x) - c1) / b1; // move player to this
}

