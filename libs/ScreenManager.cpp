#define _USE_MATH_DEFINES
extern "C" {
#include "ScreenManager.h"
}

ScreenManager::ScreenManager() {
	
}

ScreenManager::ScreenManager(GameObjectContainer* gameObjectContainer) {
	this->gameObjectContainer = gameObjectContainer;
}

void ScreenManager::decideSpriteForGameObject(DynamicGameObject* gameObject) {
	
}

// THIS SHOULD BE IN SCREEN MANAGER, make a static function
void ScreenManager::loadNextSpritePlayer(DynamicGameObject* player) {
	if (player->currentSpriteId== 1) {
		ScreenManager::loadTexture(player, PLAYER_1_FILENAME);
		player->currentSpriteId++;
	}
	else if (player->currentSpriteId == 2) {
		ScreenManager::loadTexture(player, PLAYER_2_FILENAME);
		player->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(player, PLAYER_3_FILENAME);
		player->currentSpriteId = 1;
	}
}

// THIS SHOULD BE IN SCREEN MANAGER, make a static function
void ScreenManager::loadNextSpriteBarrel(DynamicGameObject* barrel) {
	if (barrel->currentSpriteId == 1) {
		ScreenManager::loadTexture(barrel, BARREL_1_FILENAME);
		barrel->currentSpriteId++;
	}
	else if (barrel->currentSpriteId == 2) {
		ScreenManager::loadTexture(barrel, BARREL_2_FILENAME);
		barrel->currentSpriteId++;
	}
	else if (barrel->currentSpriteId == 3) {
		ScreenManager::loadTexture(barrel, BARREL_3_FILENAME);
		barrel->currentSpriteId++;
	}
	else {
		ScreenManager::loadTexture(barrel, BARREL_4_FILENAME);
		barrel->currentSpriteId = 1;
	}
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

void ScreenManager::SDLCheck() {
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
	SDL_ShowCursor(SDL_DISABLE);
}

void ScreenManager::setSDLColorKey() { 
	SDL_SetColorKey(charset, true, 0x000000);
}

void ScreenManager::serveNextFrame() { 
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
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

void ScreenManager::drawOutlineOfTheBoard() {
	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blue, black); 
}

void ScreenManager::drawAdditionalInfo() {
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

// maybe create a class in the future game object visualiser
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ScreenManager::loadTexture(GameObject* gameObject, const char* fileName) {
	gameObject->sprite = SDL_LoadBMP(fileName);
	if (gameObject->sprite == NULL) {
		printf("SDL_LoadBMP error: %s\n", SDL_GetError());
	}
}

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void ScreenManager::drawSurface(SDL_Surface* screen, GameObject* gameObject, int xpos, int ypos) {
	SDL_Rect dest;
	dest.x = xpos;
	dest.y = ypos;
	dest.w = gameObject->sprite->w;
	dest.h = gameObject->sprite->h;
	SDL_BlitSurface(gameObject->sprite, NULL, screen, &dest);
};

void ScreenManager::drawSurfaceLadder(SDL_Surface* screen, GameObject* ladder, int xpos, int ypos, SDL_Rect dest) { // not the best solution but works
	ladder->sprite->w = dest.w;
	ladder->sprite->h = dest.h;
	SDL_BlitSurface(ladder->sprite, NULL, screen, &dest);
};

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


void ScreenManager::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) { // draw a single pixel
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void ScreenManager::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) { // draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void ScreenManager::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) { // x, y - top left corner // draw a rectangle of size l by k
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++) {
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	}
};

void ScreenManager::initGameObject(GameObject* gameObject, const char* fileName) {
	loadTexture(gameObject, fileName);
}

void ScreenManager::renderGameObject(GameObject* gameObject, SDL_Surface* screen) {
	drawSurface(screen, gameObject, gameObject->xpos, gameObject->ypos);
}

void ScreenManager::renderLadder(GameObject* gameObject, SDL_Surface* screen) {
	drawSurfaceLadder(screen, gameObject, gameObject->xpos, gameObject->ypos, gameObject->destRect);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MOVE TO TEXTURE MANAGER
void ScreenManager::drawPlatforms() {
	for (int i = 0; i < gameObjectContainer->platformHolder->numberOfElements; i++) {
		gameObjectContainer->platformHolder->platforms[i].render(screen);
	}
}

// MOVE TO TEXTURE MANAGER
void ScreenManager::drawLadders() {
	for (int i = 0; i < gameObjectContainer->ladderHolder->numberOfElements; i++) {
		renderLadder(&gameObjectContainer->ladderHolder->ladders[i], screen);
	}
}

// MOVE TO TEXTURE MANAGER
void ScreenManager::drawBarrels() {
	for (int i = 0; i < gameObjectContainer->barrelDispenser->barrelHolder->numberOfElements; i++) {
		renderGameObject(&gameObjectContainer->barrelDispenser->barrelHolder->barrels[i], screen);
	}
}

// MOVE TO TEXTURE MANAGER
void ScreenManager::drawElements() { // don't repeat yourself
	renderGameObject(gameObjectContainer->donkeyKong, screen);
	renderGameObject(gameObjectContainer->princess, screen);
	renderGameObject(gameObjectContainer->player, screen);

	drawPlatforms();
	drawLadders();
	drawBarrels();
}