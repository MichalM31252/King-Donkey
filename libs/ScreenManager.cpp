#define _USE_MATH_DEFINES
#include "ScreenManager.h"
#include <string>

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

void ScreenManager::SDLCheck() const {
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

void ScreenManager::setSDLHint() const {
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
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
	if (charset == nullptr) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
	};
}

void ScreenManager::setSDLScreen() {
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

void ScreenManager::setSDLTexture() {
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void ScreenManager::hideSDLCursor() const {
	SDL_ShowCursor(SDL_DISABLE);
}

void ScreenManager::setSDLColorKey() {
	SDL_SetColorKey(charset, true, 0x000000);
}

void ScreenManager::serveNextFrame() {
	SDL_UpdateTexture(scrtex, nullptr, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, nullptr, nullptr);
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
}     

void ScreenManager::drawOutlineOfTheBoard() const {
	DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blue, black);
}

void ScreenManager::drawAdditionalInfo() {
	DrawRectangle(1, 1, SCREEN_WIDTH - 2, TOP_BAR_HEIGHT, blue, blue);

	// Convert worldTime to string and concatenate the rest of the text
	std::string text = "Time: " + std::to_string(worldTime) + " s  Score: 0  Lives: 1";

	// Call the DrawString method with the string
	DrawString(screen->w / 2 - text.length() * 8 / 2, 7, text, charset);
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

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void ScreenManager::drawSurface(const GameObject* gameObject, int xpos, int ypos) const {
	SDL_Rect dest;
	dest.x = xpos;
	dest.y = ypos;
	dest.w = gameObject->sprite->w;
	dest.h = gameObject->sprite->h;
	SDL_BlitSurface(gameObject->sprite, nullptr, screen, &dest);
}

void ScreenManager::drawSurfaceLadder(const GameObject* ladder, SDL_Rect dest) const {
	ladder->sprite->w = dest.w;
	ladder->sprite->h = dest.h;
	SDL_BlitSurface(ladder->sprite, nullptr, screen, &dest);
}

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void ScreenManager::DrawString(int x, int y, const std::string& text, SDL_Surface* charset) const {
	int px;
	int py;
	int c;
	SDL_Rect s;
	SDL_Rect d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;

	// Iterate over the string instead of char array
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


void ScreenManager::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) const { // draw a single pixel
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void ScreenManager::DrawLine(int x, int y, int l, int dx, int dy, Uint32 color) const { // draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void ScreenManager::DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) const { // x, y - top left corner // draw a rectangle of size l by k
	DrawLine(x, y, k, 0, 1, outlineColor);
	DrawLine(x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(x, y, l, 1, 0, outlineColor);
	DrawLine(x, y + k - 1, l, 1, 0, outlineColor);
	for (int i = y + 1; i < y + k - 1; i++) {
		DrawLine(x + 1, i, l - 2, 1, 0, fillColor);
	}
};

template <typename T>
void ScreenManager::loadTexture(T* gameObject, const char* fileName) {
	gameObject->sprite = SDL_LoadBMP(fileName);
	if (gameObject->sprite == nullptr) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
	}
}

template void ScreenManager::loadTexture<GameObject>(GameObject* gameObject, const char* fileName);
template void ScreenManager::loadTexture<MovableGameObject>(MovableGameObject* gameObject, const char* fileName);
template void ScreenManager::loadTexture<Barrel>(Barrel* gameObject, const char* fileName);
template void ScreenManager::loadTexture<Player>(Player* gameObject, const char* fileName);

template <typename T>
void ScreenManager::initGameObject(T* gameObject, const char* fileName) {
	loadTexture(gameObject, fileName);
}

template void ScreenManager::initGameObject<GameObject>(GameObject* gameObject, const char* fileName);
template void ScreenManager::initGameObject<MovableGameObject>(MovableGameObject* gameObject, const char* fileName);
template void ScreenManager::initGameObject<Player>(Player* gameObject, const char* fileName);

template <typename T>
void ScreenManager::renderGameObject(T* gameObject, const SDL_Surface* screen) {
	drawSurface(gameObject, gameObject->xpos, gameObject->ypos);
}

template void ScreenManager::renderGameObject<GameObject>(GameObject* gameObject, const SDL_Surface* screen);
template void ScreenManager::renderGameObject<MovableGameObject>(MovableGameObject* gameObject, const SDL_Surface* screen);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ScreenManager::renderLadder(const GameObject* gameObject) const {
	drawSurfaceLadder(gameObject, gameObject->destRect);
}

void ScreenManager::drawPlatforms() {
	for (int i = 0; i < gameObjectContainer->platformHolder->getNumberOfElements(); i++) {
		gameObjectContainer->platformHolder->platforms[i]->render(screen);
	}
}

void ScreenManager::drawLadders() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->getNumberOfElements(); i++) {
		renderLadder(std::move(gameObjectContainer->ladderHolder->ladders[i]));
	}
}

void ScreenManager::drawBarrels() {
	for (int i = 0; i < gameObjectContainer->barrelFactory->barrelHolder->getNumberOfElements(); i++) {
		renderGameObject(std::move(gameObjectContainer->barrelFactory->barrelHolder->barrels[i]), screen); // ERROR
	}
}

void ScreenManager::handlePlayerSprite(Player* player) const { // maybe const shouldn't be here ?
	if (player->isPlayerJumping()) {
		player->loadJumpingSprite();
	}
	else if (player->isClimbing) {
		player->loadNextClimbingSprite();
	}
	else if (player->isFalling) {
		player->loadJumpingSprite();
	}
	else {
		player->loadNextRunningSprite();
	}

	// is player running 
	//   after a specific amount of distance travelled change the sprite
	// is player climbing
	//   after a specific amount of distance travelled change the sprite
	// is player touching the barrel
	//  play death animation
	// is player idle
	//   play idle animation

}
//void ScreenManager::handleBarrelSprite(Barrel* barrel)
//{
//	// after a specific amount of distance travelled change the sprite
//}

void ScreenManager::drawElements() { // don't repeat yourself
	renderGameObject(gameObjectContainer->donkeyKong, screen);
	renderGameObject(gameObjectContainer->princess, screen);
	renderGameObject(gameObjectContainer->player, screen);

	drawPlatforms();
	drawLadders();
	drawBarrels();
}