#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "VisualHandler.h"
	#include "../Constants.h"
}


void VisualHandler::setColors(SDL_Surface* screen) {
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
	white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	ladderColor = SDL_MapRGB(screen->format, 0x00, 0xcf, 0xcf);
	platformColor = SDL_MapRGB(screen->format, 0xef, 0x1e, 0x4f); // just draw a line instead of a big platform
};

void VisualHandler::drawOutlineOfTheBoard(SDL_Surface* screen) { // draws the outline of the board
	this->DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, this->blue, this->black); 
}

void VisualHandler::drawAdditionalInfo(SDL_Surface* screen, double worldTime, SDL_Surface* charset) { // draws current time, score and lives on the top of the screen
	this->DrawRectangle(screen, 1, 1, SCREEN_WIDTH - 2, 18, this->blue, this->blue);
	char text[128];
	sprintf(text, "Time: %.1lf s  Score: 00000  Lives: 3", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7, text, charset);
}

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void VisualHandler::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void VisualHandler::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
// draw a single pixel
void VisualHandler::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void VisualHandler::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void VisualHandler::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) { // x, y - top left corner
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};