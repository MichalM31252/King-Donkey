#define _USE_MATH_DEFINES
#include "ScreenManager.h"
#include <string>
#include "Barrel.h"

ScreenManager::ScreenManager(GameObjectContainer* gameObjectContainer) 
	: gameObjectContainer(gameObjectContainer)
{
}

void ScreenManager::createFramerate() { // (logic) (use constructor instead) (ok what do I do with tick1 then?)
	tick1 = SDL_GetTicks();
	frames = 0; // frames that happend
	fpsTimer = 0; // 
	fps = 0; // frames per second
	worldTime = 0; // how long the game is running
}

void ScreenManager::handleDifferentComputers() {
	tick2 = SDL_GetTicks();
	deltaTime = (tick2 - tick1) * 0.001;
	tick1 = tick2;
}

void ScreenManager::updateWorldTime() {
	worldTime += deltaTime;
}

void ScreenManager::handleFPSTimer() {
	fpsTimer += deltaTime;
	if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
		fps = frames * REFRESH_RATE;
		frames = 0;
		fpsTimer -= SECONDS_BETWEEN_REFRESH;
	};
}

void ScreenManager::CheckSDL() const {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
	}
}

void ScreenManager::CreateWindowAndRenderer() {
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
	};
}

void ScreenManager::setHint() const { // use this to recieve input from window
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
}

void ScreenManager::setRenderLogicalSize() {
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ScreenManager::setDefaultDrawColor() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void ScreenManager::setWindowTitle() {
	SDL_SetWindowTitle(window, "192928 Michal Malinowski");
}

void ScreenManager::setCharset() {
	charset = SDL_LoadBMP("./assets/cs8x8.bmp");
	if (charset == nullptr) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
	};
}

void ScreenManager::setScreen() {
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void ScreenManager::setTexture() {
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ScreenManager::hideCursor() const {
	SDL_ShowCursor(SDL_DISABLE);
}

void ScreenManager::setColorKey() {
	SDL_SetColorKey(charset, true, 0x000000);
}

void ScreenManager::serveNextFrame() {
	SDL_UpdateTexture(scrtex, nullptr, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void ScreenManager::setColors() {
	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF);
}     

void ScreenManager::drawOutlineOfTheBoard() const {
	drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blue, black);
}

void ScreenManager::drawAdditionalInfo() const {
	drawRectangle(1, 1, SCREEN_WIDTH - 2, TOP_BAR_HEIGHT, blue, blue);

	// Convert worldTime to string and concatenate the rest of the text
	std::string text = "Time: " + std::to_string(worldTime) + " s  Score: 0  Lives: 1";

	drawString(screen->w / 2 - text.length() * 8 / 2, 7, text);
}

void ScreenManager::createSDL() {
	CheckSDL();
	CreateWindowAndRenderer();
	setHint();
	setRenderLogicalSize();
	setDefaultDrawColor();
	setWindowTitle();
	setCharset();
	setScreen();
	setTexture();
	hideCursor();
	setColorKey();
	setColors();
}

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void ScreenManager::drawSurface(const GameObject* gameObject, int xpos, int ypos) const {
	SDL_Rect dest = gameObject->destRect;
	dest.x = xpos;
	dest.y = ypos;
	dest.w = gameObject->sprite->w;
	dest.h = gameObject->sprite->h;
	SDL_BlitSurface(gameObject->sprite, nullptr, screen, &dest);
}

void ScreenManager::drawSurfaceLadder(const GameObject* ladder, int xpos, int ypos) const {
	SDL_Rect dest = ladder->destRect;
	dest.x = xpos;
	dest.y = ypos;
	ladder->sprite->w = dest.w;
	ladder->sprite->h = dest.h;
	SDL_BlitSurface(ladder->sprite, nullptr, screen, &dest);
}

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void ScreenManager::drawString(int x, int y, const std::string& text) const {
	int px;
	int py;
	int c;
	SDL_Rect s;
	SDL_Rect d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;

	for (char ch : text) {
		c = ch & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
	}
}

void ScreenManager::drawPixel(SDL_Surface* surface, int x, int y, Uint32 color) const { // draw a single pixel
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void ScreenManager::drawLine(int x, int y, int l, int dx, int dy, Uint32 color) const { // draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
	for (int i = 0; i < l; i++) {
		drawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void ScreenManager::drawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) const { // x, y - top left corner // draw a rectangle of size l by k
	drawLine(x, y, k, 0, 1, outlineColor);
	drawLine(x + l - 1, y, k, 0, 1, outlineColor);
	drawLine(x, y, l, 1, 0, outlineColor);
	drawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (int i = y + 1; i < y + k - 1; i++) {
		drawLine(x + 1, i, l - 2, 1, 0, fillColor);
	}
};

template <typename T>
void ScreenManager::loadTexture(T* gameObject, const char* fileName) {
	gameObject->sprite = SDL_LoadBMP(fileName);
	if (gameObject->sprite == nullptr) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
		return;
	}
}

template void ScreenManager::loadTexture<GameObject>(GameObject* gameObject, const char* fileName);
template void ScreenManager::loadTexture<MovableGameObject>(MovableGameObject* gameObject, const char* fileName);
template void ScreenManager::loadTexture<Barrel>(Barrel* gameObject, const char* fileName);
template void ScreenManager::loadTexture<Player>(Player* gameObject, const char* fileName);
template void ScreenManager::loadTexture<Gorilla>(Gorilla* gameObject, const char* fileName);

void ScreenManager::flipTextureHorizontally(SDL_Surface* sprite) {
	int width = sprite->w;
	int height = sprite->h;
	int pitch = sprite->pitch;
	int bpp = sprite->format->BytesPerPixel;

	unsigned char* pixels = static_cast<unsigned char*>(sprite->pixels);

	for (int y = 0; y < height; y++) {
		unsigned char* row = pixels + y * pitch;
		for (int x = 0; x < width / 2; x++) {
			for (int b = 0; b < bpp; b++) {
				std::swap(row[x * bpp + b], row[(width - 1 - x) * bpp + b]);
			}
		}
	}
}

void ScreenManager::renderLadder(const GameObject* gameObject) const {
	// drawSurface(gameObject, gameObject->xpos, gameObject->ypos);
	drawSurfaceLadder(gameObject, gameObject->xpos, gameObject->ypos);
}

void ScreenManager::drawPlatforms() {
	for (int i = 0; i < gameObjectContainer->platformContainer->getNumberOfElements(); i++) {
		gameObjectContainer->platformContainer->platforms[i]->render(screen);
	}
}

void ScreenManager::drawLadders() {
	for (int i = 0; i < gameObjectContainer->ladderContainer->getNumberOfElements(); i++) {
		renderLadder(std::move(gameObjectContainer->ladderContainer->ladders[i]));
	}
}

void ScreenManager::drawBarrels() {
	for (int i = 0; i < gameObjectContainer->barrelContainer->getNumberOfElements(); i++) {
		drawSurface(gameObjectContainer->barrelContainer->barrels[i], gameObjectContainer->barrelContainer->barrels[i]->xpos, gameObjectContainer->barrelContainer->barrels[i]->ypos);
	}
}

void ScreenManager::drawElements() {
	drawPlatforms();
	drawLadders();
	drawBarrels();
	
	drawSurface(gameObjectContainer->donkeyKong, gameObjectContainer->donkeyKong->xpos, gameObjectContainer->donkeyKong->ypos);
	drawSurface(gameObjectContainer->princess, gameObjectContainer->princess->xpos, gameObjectContainer->princess->ypos);
	drawSurface(gameObjectContainer->player, gameObjectContainer->player->xpos, gameObjectContainer->player->ypos);
}