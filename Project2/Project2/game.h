#pragma once

int players;
int player1, player2;
int scores[3];
int mode;
int esc;
int dir1, dir2;
int nextLine1, nextLine2;
int balls;
int shoot1, shoot2;
int rp, wp;
int helpToggle1, helpToggle2;

time_t TIME, DUR;
time_t TIME1, TIME2;
time_t HELP1, HELP2;
time_t REVERSE1, REVERSE2;
time_t MASK1, MASK2;

int items[3][7]; // ������0 ����1 ����2 ��ź3 �ݴ��4 ��ȯ5 �Ⱥ��̰�6
int remains[3];

typedef struct
{
	int y, x;
} LOC;
LOC queue[150];
LOC helps[3];

int visited[15][15];

void initGame();

void initTimer();

void game();

void move(int playerNo);

void draw(int playerNo);

void score(int playerNo);

int deadCheck(int playerNo);

void gameOver(int playerNo);