#pragma once

// Window constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int STARTING_X = 0;
const int STARTING_Y = 0;

const int TOP_BAR_HEIGHT = 18;

// Platform 
const int MAXIMUM_AMOUNT_OF_PLATFORMS = 100;

// Refresh constants
const double SECONDS_BETWEEN_REFRESH = 0.5;
const double REFRESH_RATE = 1.0 / SECONDS_BETWEEN_REFRESH;

// GameObject Const
const int STARTING_X_PLAYER = 50;
const int STARTING_Y_PLAYER = 350;

const int STARTING_X_DONKEY_KONG = 64;
const int STARTING_Y_DONKEY_KONG = 64;

const double DEFAULT_PLAYER_SPEED = 200;
const double DEFAULT_BARREL_SPEED = 200;

const double DEFAULT_GRAVITY = 100;

// Source File constants
// YOU CAN"T PLACE DEFINES IN DIFFERENT FILES
//#define SDL_PATH ./SDL2-2.0.10/include/SDL.h
//#define SDL_MAIN_PATH ./SDL2-2.0.10/include/SDL_main.h
//#define FROM_LIBS_TO_MAIN "/."
//#define FROM_GAME__TO_MAIN "../."