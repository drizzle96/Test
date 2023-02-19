#pragma once

typedef enum 
{
	BLUE = 9,
	GREEN,
	SKYBLUE,
	RED,
	PINK,
	YELLOW,
	WHITE
} COLORS;

typedef enum 
{
	OPTION_X = 20,
	OPTION_Y = 12,
	DETAIL = 10,
	SCORE_1P_X = 2,
	SCORE_2P_X = 30,
	SCORE_Y = 16,
	BALL_Y = 12
} LOCATIONS;

typedef enum 
{
	HOWTO = 1,
	NORMAL_GAME = 0,
	LIMITED_GAME,
	VSMODE_GAME
} SETTINGS;

typedef enum 
{
	ENT = 13,
	ESC = 27,
	SPC = 32,
	UP = 72,
	LEFT = 75,
	RIGHT =77,
	DOWN = 80
} KEYS;

typedef enum 
{
	TIMING = 100,
	NEXTBALL = 15000,
	COLBOMB = -10,
	ROWBOMB = -20,
	BOXBOMB = -30,
	WALL = -1,
	EMPTY = 0,
	HELPLINE = 1000,
	ARROW = 2,
	HELPTIME = 5000,
	REVETIME = 5000,
	MASKTIME = 5000
} GAME;

typedef enum
{
	ELFO = 0,
	SELECT = 1,
	SHOOT = 2,
	BOMB = 3,
	END = 4,
	ATK = 5,
	GUN = 6,
	YEAH = 7,
	CHANGE = 8,
	LOBBY = 9,
	MAIN = 10,
	MORE = 11,
	SHA = 12
} SOUND;