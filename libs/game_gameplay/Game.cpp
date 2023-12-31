#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>

extern "C" {
	#include "../../SDL2-2.0.10/include/SDL.h"
	#include "../../SDL2-2.0.10/include/SDL_main.h"

	#include "Game.h"
	#include "../Constants.h"
	#include "../game_visual/DrawHandler.h"
}

Game::Game(){
	quit = 0;
}

void Game::initEverything() {
	int tick1, tick2, frames, rc;
	double deltaTime, worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface* screen, * charset; // screen on which we will be drawing, charset is the bitmap with characters
	SDL_Surface* eti; // picture of eti
	SDL_Texture* scrtex; // ?? probably useless
	SDL_Window* window; // widnows window
	SDL_Renderer* renderer; // we send here to render the screen

	DrawHandler drawHandler;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		this->closeGame();
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0) {
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		this->closeGame();
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "192928 Michal Malinowski");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("./cs8x8.bmp"); // this function is for reading bmp files
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		this->closeGame(charset, screen, scrtex, window, renderer);
	};
	SDL_SetColorKey(charset, true, 0x000000);

	eti = SDL_LoadBMP("./eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		this->closeGame(charset, screen, scrtex, window, renderer);
	};

	char text[128];
	const int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	const int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	const int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	const int blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	const int white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);

	const int ladderColor = SDL_MapRGB(screen->format, 0x00, 0xcf, 0xcf);
	const int platformColor = SDL_MapRGB(screen->format, 0xef, 0x1e, 0x4f); // just draw a line instead of a big platform

	tick1 = SDL_GetTicks();

	frames = 0; // frames tha happend
	fpsTimer = 0; // 
	fps = 0; // frames per second

	worldTime = 0; // how long the game is running
	distance = 0; // the distance of the eti sign (this could maybe work for collision detection)
	etiSpeed = 1; // speed of the eti sign

	while (true) { // 1 frame of the game
		tick2 = SDL_GetTicks();
		deltaTime = (tick2 - tick1) * 0.001; // deltaTime is time in miliseconds since the last screen was drawn to make sure that the game runs at the same speed on different computers
		tick1 = tick2;

		worldTime += deltaTime;

		distance += etiSpeed * deltaTime;

		SDL_FillRect(screen, NULL, platformColor);

		// draws the eti.bmp image, for drawing 	                        
		drawHandler.DrawSurface(screen, eti, SCREEN_WIDTH / 2 + sin(distance) * SCREEN_HEIGHT / 3, SCREEN_HEIGHT / 2 + cos(distance) * SCREEN_HEIGHT / 3); // an image on the specified position	

		fpsTimer += deltaTime;
		if (fpsTimer > SECONDS_BETWEEN_REFRESH) {
			fps = frames * REFRESH_RATE;
			frames = 0;
			fpsTimer -= SECONDS_BETWEEN_REFRESH;
		};

		// tekst informacyjny / info text
		drawHandler.DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blue, black); // draws border around the whole screen
		drawHandler.DrawRectangle(screen, 1, 1, SCREEN_WIDTH - 2, 18, blue, blue);

		sprintf(text, "Time: %.1lf s  Score: 00000  Lives: 3", worldTime); //            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
		drawHandler.DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 7, text, charset);


		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);



		// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					this->closeGame(charset, screen, scrtex, window, renderer);
				else if (event.key.keysym.sym == SDLK_UP)
					etiSpeed = 2.0;
				else if (event.key.keysym.sym == SDLK_DOWN)
					etiSpeed = 0.3;
				break;
			case SDL_KEYUP:
				etiSpeed = 1.0;
				break;
			case SDL_QUIT:
				this->closeGame(charset, screen, scrtex, window, renderer);
				break;
			};
		};
		frames++;
	};
	this->closeGame(charset, screen, scrtex, window, renderer);
}

void Game::closeGame(){
	SDL_Quit();
	exit(0);
}

void Game::closeGame(SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer) {
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	exit(0);
}
