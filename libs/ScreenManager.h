#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "MovableGameObject.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "Barrel.h"
#include "Player.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include <string>

class ScreenManager {
public:
	GameObjectContainer* gameObjectContainer;

	int tick1;
	int tick2;
	int frames;

	double deltaTime;
	double worldTime;
	double fpsTimer;
	double fps;

	Uint32 black;
	Uint32 green;
	Uint32 red;
	Uint32 blue;
	Uint32 white;

	Uint32 ladderColor;
	Uint32 platformColor;

	int rc;
	SDL_Surface* screen; // screen on which we will be drawing, charset is the bitmap with characters
	SDL_Surface* charset; // screen on which we will be drawing, charset is the bitmap with characters
	SDL_Texture* scrtex; // 
	SDL_Window* window; // widnows window
	SDL_Renderer* renderer; // we send here to render the screen

	ScreenManager() = default;
	explicit ScreenManager(GameObjectContainer* gameObjectContainer);

	void SDLCheck() const;
	void SDLCreateWindowAndRenderer();
	void setSDLHint() const;
	void setSDLRenderLogicalSize();
	void setSDLDefaultDrawColor();
	void setSDLWindowTitle();
	void setSDLCharset();
	void setSDLScreen();
	void setSDLTexture();

	void hideSDLCursor() const;
	void setSDLColorKey();

	void setColors();
	void drawOutlineOfTheBoard() const ;
	void drawAdditionalInfo();
	void createSDL();

	void createFramerate();
	void handleFPSTimer();
	void handleDifferentComputers();
	void updateWorldTime();

	void serveNextFrame();

	void drawSurface(const GameObject* gameObject, int xpos, int ypos) const;
	void drawSurfaceLadder(const GameObject* ladder, SDL_Rect dest) const;
	void DrawString(int x, int y, const std::string& text, SDL_Surface* charset) const;
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) const;
	void DrawLine(int x, int y, int l, int dx, int dy, Uint32 color) const;
	void DrawRectangle(int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) const;

	template <typename T>
	static void initGameObject(T* gameObject, const char* fileName);

	template <typename T>
	static void loadTexture(T* gameObject, const char* fileName);

	template<typename T>
	void renderGameObject(T* gameObject) const;

	void renderLadder(const GameObject* gameObject) const;

	void drawElements();
	void drawPlatforms();
	void drawLadders();
	void drawBarrels();

	void handlePlayerSprite(Player* player) const;
	// void handleBarrelSprite(Barrel* barrel);
};