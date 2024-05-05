#define _USE_MATH_DEFINES
extern "C" {
#include "ScreenManager.h"
}

// MOVE TO SCREEN MANAGER ? 
void ScreenManager::createFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

// move to screen manager
void ScreenManager::handleDifferentComputers() { // (logic) make every object dependent on deltaTime so it works the same on different computers
	tick2 = SDL_GetTicks();
	deltaTime = (tick2 - tick1) * 0.001;
	tick1 = tick2;
}

// move to screen manager ???
void ScreenManager::updateWorldTime() {
	worldTime += deltaTime;
}

// move to screen manager
void ScreenManager::handleFPSTimer() {
	fpsTimer += deltaTime;
	if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
		fps = frames * REFRESH_RATE;
		frames = 0;
		fpsTimer -= SECONDS_BETWEEN_REFRESH;
	};
}

void ScreenManager::SDLCheck() { // checks if SDL was initialized correctly
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
	}
}

void ScreenManager::SDLCreateWindowAndRenderer() { 
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	};
}

void ScreenManager::setSDLHint() { 
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void ScreenManager::setSDLRenderLogicalSize() { 
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ScreenManager::setSDLDefaultDrawColor() { 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void ScreenManager::setSDLWindowTitle() { 
	SDL_SetWindowTitle(window, "192928 Michal Malinowski");
}

void ScreenManager::setSDLCharset() { 
	charset = SDL_LoadBMP("./assets/cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
	};
}

void ScreenManager::setSDLScreen() { 
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void ScreenManager::setSDLTexture() { 
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ScreenManager::hideSDLCursor() { 
	SDL_ShowCursor(SDL_DISABLE); // hides the cursor
}

void ScreenManager::setSDLColorKey() { 
	SDL_SetColorKey(charset, true, 0x000000);
}

void ScreenManager::serveNextFrame() { 
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL); // scrtex here is what we want to render
	SDL_RenderPresent(renderer); 
}

void ScreenManager::setColors() {
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
	white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	ladderColor = SDL_MapRGB(screen->format, 0x00, 0xcf, 0xcf);
	platformColor = SDL_MapRGB(screen->format, 0xef, 0x1e, 0x4f);
};

void ScreenManager::drawOutlineOfTheBoard() { // draws the outline of the board
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blue, black); 
}

void ScreenManager::drawAdditionalInfo(double worldTime) { // draws current time, score and lives on the top of the screen
	DrawRectangle(screen, 1, 1, SCREEN_WIDTH - 2, TOP_BAR_HEIGHT, blue, blue);
	char text[128];
	sprintf(text, "Time: %.1lf s  Score: 00000  Lives: 1", worldTime);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7, text, charset);
}

void ScreenManager::createSDL() {
	SDLCheck();
	SDLCreateWindowAndRenderer();
	setSDLHint();
	setSDLRenderLogicalSize();
	setSDLDefaultDrawColor();
	setSDLWindowTitle();
	setSDLCharset();
	setSDLScreen();
	setSDLTexture();
	hideSDLCursor();
	setSDLColorKey();
	setColors();
}

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void ScreenManager::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
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

// draw a single pixel
void ScreenManager::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void ScreenManager::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// draw a rectangle of size l by k
void ScreenManager::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) { // x, y - top left corner
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};