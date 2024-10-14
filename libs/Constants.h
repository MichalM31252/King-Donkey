#pragma once

// Window constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int STARTING_X = 0;
const int STARTING_Y = 0;

const int TOP_BAR_HEIGHT = 18;

const int TINY_MARGIN = 1;
const int SMALL_MARGIN = 5;
const int MEDIUM_MARGIN = 25;
const int LARGE_MARGIN = 100;

// Board constants
const int BOARD_ID_A = 1;
const int BOARD_ID_B = 2;
const int BOARD_ID_C = 3;

// Platform 
const int MAXIMUM_AMOUNT_OF_PLATFORMS = 1000;
const int MAXIMUM_AMOUNT_OF_LADDERS = 1000;
const int MAXIMUM_AMOUNT_OF_BARRELS = 1000;

// Ladder 
const int LADDER_WIDTH = 45;

// Refresh constants
const double SECONDS_BETWEEN_REFRESH = 0.5;
const double REFRESH_RATE = 1.0 / SECONDS_BETWEEN_REFRESH;

// GameObject Const
const int STARTING_X_PLAYER = 50;
const int STARTING_Y_PLAYER = 300;
const int DEFAULT_JUMP_HEIGHT = 60; // check 60 for jumping onto platforms

const int STARTING_X_DONKEY_KONG = 64;
const int STARTING_Y_DONKEY_KONG = 64;
const int DONKEY_KONG_WIDTH = 80;

const int STARTING_X_PRINCESS = 200;
const int STARTING_Y_PRINCESS = 32;

const double DEFAULT_PLAYER_SPEED = 200;
const double DEFAULT_BARREL_SPEED = 50;
const double DEFAULT_BARREL_SPAWN_RATE = 3.0;

const double DEFAULT_GRAVITY = 100;

// Player
const char PLAYER_1_FILENAME[] = "./assets/Mario_Run1.bmp";
const char PLAYER_2_FILENAME[] = "./assets/Mario_Run2.bmp";
const char PLAYER_3_FILENAME[] = "./assets/Mario_Run3.bmp";

const char PLAYER_CLIMB_1[] = "./assets/Mario_Climb1.bmp";
const char PLAYER_CLIMB_2[] = "./assets/Mario_Climb2.bmp";

// Barrel 
const char BARREL_1_FILENAME[] = "./assets/Barrel_1.bmp";
const char BARREL_2_FILENAME[] = "./assets/Barrel_2.bmp";
const char BARREL_3_FILENAME[] = "./assets/Barrel_3.bmp";
const char BARREL_4_FILENAME[] = "./assets/Barrel_4.bmp";
