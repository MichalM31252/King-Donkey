#pragma once

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "MovableGameObject.h"
#include "Constants.h"
#include "GameObjectContainer.h"
#include "Player.h"
#include "../SDL2-2.0.10/include/SDL.h"
#include "../SDL2-2.0.10/include/SDL_main.h"
#include <string>

class ScreenManager {
public:
	std::shared_ptr<GameObjectContainer> gameObjectContainer;

	int frames;
	double fpsTimer;
	double fps;

	// create a structure for colors
	Uint32 black;
	Uint32 blue;

	int rc;
	SDL_Surface* screen; // screen on which we will be drawing, charset is the bitmap with characters
	SDL_Surface* charset; // screen on which we will be drawing, charset is the bitmap with characters
	SDL_Texture* scrtex; // 
	SDL_Window* window; // widnows window
	SDL_Renderer* renderer; // we send here to render the screen

	ScreenManager() = default;
	explicit ScreenManager(std::shared_ptr<GameObjectContainer> gameObjectContainer);

	void checkSDL() const;
	void createWindowAndRenderer();
	void setHint() const;
	void setRenderLogicalSize();
	void setDefaultDrawColor();
	void setWindowTitle();
	void setCharset();
	void setScreen();
	void setTexture();
	void hideCursor() const;
	void setColorKey();

	void setColors();
	void drawOutlineOfTheBoard() const;
	void drawAdditionalInfo(double deltaTime) const;

	void createFramerate();
	void handleFPSTimer(double deltaTime);

	void serveNextFrame();

	void drawSurface(std::shared_ptr<GameObject> gameObject, int xpos, int ypos) const;
	void drawSurfaceLadder(std::shared_ptr<GameObject> ladder, int xpos, int ypos) const;
	void drawString(int x, int y, const std::string& text) const;
	void drawPixel(SDL_Surface* surface, int x, int y, Uint32 color) const;
	void drawLine(int x, int y, int l, int dx, int dy, Uint32 color) const;
	void drawRectangle(int x, int y, int widthOfRectangle, int heightOfRectangle, Uint32 outlineColor, Uint32 fillColor) const;
	void drawPlatorm(std::shared_ptr<Platform> platform);

	template <typename T>
	static void loadTexture(T* gameObject, const char* fileName);
	static void flipTextureHorizontally(SDL_Surface* sprite);

	void drawElements();
	void drawPlatforms();
	void drawLadders();
	void drawBarrels();

	static void drawMenu();
};