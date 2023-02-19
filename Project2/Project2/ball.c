#pragma once
#include "main.h"

void initBoard()
{
	memset(board_1p, 0, sizeof(board_1p));
	memset(board_2p, 0, sizeof(board_1p));

	next[1].color = next[2].color = (rand() % balls) + 3;

	for (int i = 0; i < 14; i++)
	{
		board_1p[i][0] = board_1p[i][10] = -1;
		if (i < 11)
		{
			board_1p[14][i] = -1;
		}
	}
	board_1p[13][5] = ARROW;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j < 9; j+=2)
		{
			board_1p[i][j] = board_1p[i][j + 1] = ((rand() + j) % balls) + 3;
		}
		board_1p[i][9] = (rand() % balls) + 3;
	}
	
	setColor(15, 0);
	gotoxy(SCORE_1P_X, SCORE_Y);
	printf("SCORE");
	gotoxy(SCORE_1P_X + 15, SCORE_Y - 1);
	printf("NEXT");

	if (mode == 1)
	{
		gotoxy(SCORE_1P_X, SCORE_Y + 1);
		printf("REMAIN");
		gotoxy(SCORE_1P_X + 6, SCORE_Y + 1);
		printf("%4d", remains[1]);
	}

	if (players == 2)
	{
		memcpy(board_2p, board_1p, sizeof(board_2p));
		setColor(15, 0);
		gotoxy(SCORE_2P_X, SCORE_Y);
		printf("SCORE");
		gotoxy(SCORE_2P_X + 15, SCORE_Y - 1);
		printf("NEXT");

		if (mode == 1)
		{
			gotoxy(SCORE_2P_X, SCORE_Y + 1);
			printf("REMAIN");
			gotoxy(SCORE_2P_X + 6, SCORE_Y + 1);
			printf("%4d", remains[2]);
		}
	}
}

void initBall(int playerNo)
{
	if (playerNo == 1)
	{
		ball[1].y = BALL_Y;
		ball[1].x = dir1;
		ball[1].color = next[1].color;
		next[1].color =	(rand() % balls) + 3;
		board_1p[BALL_Y][dir1] = ball[1].color;

		gotoxy(SCORE_1P_X + 16, SCORE_Y);
		setColor(next[1].color, 0);
		printf("¡Ü");
	}
	if (playerNo == 2)
	{
		ball[2].y = BALL_Y;
		ball[2].x = dir2;
		ball[2].color = next[2].color;
		next[2].color = (rand() % balls) + 3;
		board_2p[BALL_Y][dir2] = ball[2].color;

		gotoxy(SCORE_2P_X + 16, SCORE_Y);
		setColor(next[2].color, 0);
		printf("¡Ü");
	}
}

void down(int playerNo)
{
	if (playerNo == 1)
	{
		for (int i = 11; i >= 1; i--)
		{
			for (int j = 1; j < 10; j++)
			{
				board_1p[i][j] = board_1p[i - 1][j];
			}
		}
		for (int j = 1; j < 10; j++)
		{
			board_1p[0][j] = rand() * j % balls + 3;
		}
	}
	else
	{
		for (int i = 11; i >= 1; i--)
		{
			for (int j = 1; j < 10; j++)
			{
				board_2p[i][j] = board_2p[i - 1][j];
			}
		}
		for (int j = 1; j < 10; j++)
		{
			board_2p[0][j] = rand() * j % balls + 3;
		}
	}
}

void swapBoard()
{
	int temp[15][11];
	
	for (int i = 0; i < 12; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			temp[i][j] = board_1p[i][j];
			board_1p[i][j] = board_2p[i][j];
			board_2p[i][j] = temp[i][j];
			if (board_1p[i][j] == HELPLINE) board_1p[i][j] = EMPTY;
			if (board_2p[i][j] == HELPLINE) board_2p[i][j] = EMPTY;
		}
	}
}

void helpLine(int playerNo)
{
	int x;
	int y = 12;

	if (playerNo == 1)
	{
		x = dir1;

		while (board_1p[y - 1][x] == 0)
		{
			board_1p[--y][x] = HELPLINE;
			if (y == 0) break;
		}
		helps[1].x = x;
		helps[1].y = y;
	}

	else
	{
		x = dir2;

		while (board_2p[y - 1][x] == 0)
		{
			board_2p[--y][x] = HELPLINE;
			if (y == 0) break;
		}
		helps[2].x = x;
		helps[2].y = y;
	}
}

void deleteHelpLine(int playerNo)
{
	int x, y;

	if (playerNo == 1)
	{
		x = helps[1].x;
		y = helps[1].y;

		for (int i = y; i <= 11; i++)
		{
			if (board_1p[i][x] == HELPLINE) board_1p[i][x] = 0;
		}
	}
	else
	{
		x = helps[2].x;
		y = helps[2].y;

		for (int i = y; i <= 11; i++)
		{
			if (board_2p[i][x] == HELPLINE) board_2p[i][x] = 0;
		}
	}
}

void check(int playerNo)
{
	if (playerNo == 1) BFS(1);
	else BFS(2);
}

void BFS(int playerNo)
{
	int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int cnt = 1;
	int color = 0;
	rp = wp = 0;
	memset(queue, 0, sizeof(queue));
	memset(visited, 0, sizeof(visited));

	if (playerNo == 1)
	{
		int x = ball[1].x;
		int y = ball[1].y;
		color = ball[1].color;

		if (color == COLBOMB)
		{
			for (int i = y; i >= 0; i--) board_1p[i][x] = 35;
			playingSound(BOMB);
			return;
		}
		else if (color == ROWBOMB)
		{
			for (int i = 1; i < 10; i++) board_1p[y][i] = 35;
			playingSound(BOMB);
			return;
		}
		else if (color == BOXBOMB)
		{
			for (int i = y - 1; i <= y + 1; i++)
			{
				for (int j = x - 1; j <= x + 1; j++)
				{
					if (i < 0 || i == 12 || j == 10) break;
					if (j == 0) continue;
					board_1p[i][j] = 35;
				}
			}
			playingSound(BOMB);
			return;
		}

		queue[wp].y = y;
		queue[wp++].x = x;
		visited[y][x] = 1;
	}

	else
	{
		int x = ball[2].x;
		int y = ball[2].y;
		color = ball[2].color;

		if (color == COLBOMB)
		{
			for (int i = y; i >= 0; i--) board_2p[i][x] = 35;
			playingSound(BOMB);
			return;
		}
		else if (color == ROWBOMB)
		{
			for (int i = 1; i < 10; i++) board_2p[y][i] = 35;
			playingSound(BOMB);
			return;
		}
		else if (color == BOXBOMB)
		{
			for (int i = y - 1; i <= y + 1; i++)
			{
				for (int j = x - 1; j <= x + 1; j++)
				{
					if (i < 0 || i >= 12 || j == 10) break;
					if (j == 0) continue;
					board_2p[i][j] = 35;
				}
			}
			playingSound(BOMB);
			return;
		}

		queue[wp].y = y;
		queue[wp++].x = x;
		visited[y][x] = 1;
	}

	while (rp != wp)
	{
		int cy = queue[rp].y;
		int cx = queue[rp++].x;

		for (int i = 0; i < 8; i++)
		{
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (ny < 0 || ny > 11 || nx < 1 || nx > 9) continue;
			if (visited[ny][nx] == 1) continue;
			if (playerNo == 1)
			{
				if (board_1p[ny][nx] == color)
				{
					queue[wp].y = ny;
					queue[wp++].x = nx;
					visited[ny][nx] = 1;
					cnt++;
				}
			}
			else
			{
				if (board_2p[ny][nx] == color)
				{
					queue[wp].y = ny;
					queue[wp++].x = nx;
					visited[ny][nx] = 1;
					cnt++;
				}
			}
		}
	}

	if (cnt > 2)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				if (visited[i][j] == 1)
				{
					if (playerNo == 1) board_1p[i][j] += 20;
					else board_2p[i][j] += 20;
				}
			}
		}
	}
}

