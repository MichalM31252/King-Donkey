#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "VisualManager.h"
	#include "../Constants.h"
}

void VisualManager::SDLCheck() { // checks if SDL was initialized correctly
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		// this->closeGame();
	}
}

void VisualManager::SDLCreateWindowAndRenderer() { // visual
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		// this->closeGame();
	};
}

void VisualManager::SDLSetHint() { // visual
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void VisualManager::SDLSetRenderLogicalSize() { // visual
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void VisualManager::SDLSetDefaultDrawColor() { // visual
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void VisualManager::SDLSetWindowTitle() { // visual
	SDL_SetWindowTitle(window, "192928 Michal Malinowski");
}

void VisualManager::SDLSetCharset() { // visual
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		// this->closeGame(charset, screen, scrtex, window, renderer);
	};
}

void VisualManager::SDLSetScreen() { // visual
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void VisualManager::SDLSetTexture() { // visual
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void VisualManager::SDLSetEtiLogo() { // visual
	eti = SDL_LoadBMP("./eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		// this->closeGame(charset, screen, scrtex, window, renderer);
	};
}

void VisualManager::SDLHideCursor() { // visual
	SDL_ShowCursor(SDL_DISABLE); // hides the cursor
}

void VisualManager::SDLSetColorKey() { // visual
	SDL_SetColorKey(charset, true, 0x000000);
}

void VisualManager::serveNextFrame() { // visual
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void VisualManager::setColors() {
	black = SDL_MapRGB(this->screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(this->screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(this->screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(this->screen->format, 0x00, 0x00, 0xFF);
	white = SDL_MapRGB(this->screen->format, 0xFF, 0xFF, 0xFF);
	ladderColor = SDL_MapRGB(this->screen->format, 0x00, 0xcf, 0xcf);
	platformColor = SDL_MapRGB(this->screen->format, 0xef, 0x1e, 0x4f); // just draw a line instead of a big platform
};

void VisualManager::drawOutlineOfTheBoard() { // draws the outline of the board
	this->DrawRectangle(this->screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, this->blue, this->black); 
}

void VisualManager::drawAdditionalInfo(double worldTime) { // draws current time, score and lives on the top of the screen
	this->DrawRectangle(screen, 1, 1, SCREEN_WIDTH - 2, 18, this->blue, this->blue);
	char text[128];
	sprintf(text, "Time: %.1lf s  Score: 00000  Lives: 3", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7, text, charset);
}

void VisualManager::setUpVisuals() {
	this->SDLCheck();
	this->SDLCreateWindowAndRenderer();
	this->SDLSetHint();
	this->SDLSetRenderLogicalSize();
	this->SDLSetDefaultDrawColor();
	this->SDLSetWindowTitle();
	this->SDLSetCharset();
	this->SDLSetScreen();
	this->SDLSetTexture();
	this->SDLSetEtiLogo();
	this->SDLHideCursor();
	this->SDLSetColorKey();
	this->setColors();
}

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void VisualManager::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
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
void VisualManager::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
// draw a single pixel
void VisualManager::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void VisualManager::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void VisualManager::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) { // x, y - top left corner
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};