#pragma once

typedef struct
{
	int y, x, color;
} BALL;
BALL ball[3];
BALL next[3];

int board_1p[15][11];
int board_2p[15][11];

void initBoard();

void initBall(int playerNo);

void down(int playerNo);

void swapBoard();

void helpLine(int playerNo);

void deleteHelpLine(int playerNo);

void check(int playerNo);

void BFS(int playerNo);