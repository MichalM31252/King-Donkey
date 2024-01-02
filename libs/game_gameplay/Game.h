#pragma once

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"
	#include "../game_visual/VisualHandler.h"
	#include "./EventHandler.h"
}

class Game {
	public:
		// logic
		int tick1, tick2, frames;
		double deltaTime, worldTime, fpsTimer, fps;
		double distance, etiSpeed; // this can be used here

		// visual
		int rc;
		SDL_Surface* screen, * charset; // screen on which we will be drawing, charset is the bitmap with characters
		SDL_Surface* eti; // picture of eti
		SDL_Texture* scrtex; // ?? probably useless
		SDL_Window* window; // widnows window
		SDL_Renderer* renderer; // we send here to render the screen

		// Game(); Constructor NEEDED ADD DEFAULT VALUES
		void initGame();

		void SDLCheck();
		void SDLCreateWindowAndRenderer();
		void SDLSetHint();
		void SDLSetRenderLogicalSize();
		void SDLSetDefaultDrawColor();
		void SDLSetWindowTitle();
		void SDLSetCharset();
		void SDLSetScreen();
		void SDLSetTexture();
		void SDLSetEtiLogo();
		void SDLHideCursor();
		void SDLSetColorKey();
		void setUpFramerate();
		void setUpGameObjects();
		void handleFPSTimer();
		void handleDifferentComputers();
		void updateWorldTime();
		void serveNextFrame();

		void handleGame(VisualHandler& visualHandler, EventHandler& eventHandler);

		void closeGame();
		void closeGame(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer);
};