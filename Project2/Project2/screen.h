#pragma once

typedef struct
{
	char name[10];
	int rank, score;
} RANK;
RANK rank1[10];
RANK rank2[10];

void cursorView(int isVisible);

void gotoxy(int x, int y);

void setColor(int text, int back);

void nextButton();
int upDownButton(int optionNum);

void optionClear(int rows);
void detailClear(int rows);

int title();

void howto();

void selectPlayer();
void selectMode();

void ranking();