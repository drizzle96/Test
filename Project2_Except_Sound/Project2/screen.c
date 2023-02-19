# include "main.h"

void cursorView(int isVisible)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	if (isVisible == 0)
	{
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = 0;
	}
	else
	{
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = 1;
	}
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int text, int back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void nextButton()
{
	while (TRUE)
	{
		if (_kbhit())
		{
			playingSound(1);
			if (_getch() == ESC) esc = 1;
			return;
		}
	}
}

int upDownButton(int optionNum)
{
	int select = 0;
	char c;

	while (TRUE)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == ESC)
			{
				playingSound(1);
				esc = 1;
				return;
			}
			if (c == ENT || c == SPC)
			{
				playingSound(1);
				return select;
			}
			if (c == -32)
			{
				c = _getch();
				switch (c)
				{
				case UP:
					select--;
					if (select == -1) select = optionNum - 1;
					break;
				case DOWN:
					select++;
					if (select == optionNum) select = 0;
					break;
				}
			}
		}
		gotoxy(OPTION_X - 2, OPTION_Y + select * 2);
	}
	return select;
}

void optionClear(int rows)
{
	for (int i = 0; i < rows; i++)
	{
		gotoxy(OPTION_X, OPTION_Y + 2 * i);
		printf("                                   ");
	}
}

void detailClear(int rows)
{
	for (int i = 0; i < rows; i++)
	{
		gotoxy(0, DETAIL + i);
		printf("                                                  ");
	}
}

int title()
{
	cursorView(0);
	setColor(0, 0);
	playingSong(ELFO, FALSE);

	system("cls");
	
	printf("\n\n\n");
	setColor(SKYBLUE, 0);
	printf("      ___ _  _ ___ ___ __  ____    ____ _ ___\n");
	setColor(PINK, 0);
	printf("     | o ) |_|| o ) o ) /_/ o__＼ | o_)o | o_)\n");
	setColor(YELLOW, 0);
	printf("     |_O_)____/_O_)_O_)___＼___/  |_| |__|_|\n");

	char c;
	int select = 0;

	setColor(WHITE, 0);

	cursorView(1);

	gotoxy(OPTION_X, OPTION_Y);
	printf("START GAME");
	gotoxy(OPTION_X, OPTION_Y + 2);
	printf("HOW TO PLAY");

	return upDownButton(2);
}

void howto()
{
	cursorView(0);
	playingSong(LOBBY, FALSE);
	optionClear(2);
	
	// 개요
	setColor(YELLOW, 0);
	gotoxy(DETAIL, DETAIL);
	printf("BUBBLE POP은 구슬을 발사해서");
	setColor(WHITE, 0);
	gotoxy(DETAIL, DETAIL + 1);
	printf("상하좌우 및 대각선으로");
	setColor(YELLOW, 0);
	gotoxy(DETAIL, DETAIL + 2);
	printf("같은 색의 구슬을 3개 이상 모아");
	setColor(WHITE, 0);
	gotoxy(DETAIL, DETAIL + 3);
	printf("터뜨리는 게임입니다.");
	setColor(YELLOW, 0);
	gotoxy(DETAIL, DETAIL + 5);
	printf("한 번에 구슬을 많이 떨어뜨릴수록");
	setColor(WHITE, 0);
	gotoxy(DETAIL, DETAIL + 6);
	printf("높은 점수를 얻을 수 있습니다.");
	
	nextButton();
	if (esc == 1) return;
	detailClear(7);

	// 조작키
	gotoxy(DETAIL, DETAIL);
	setColor(RED, 0);
	printf(" 1인게임            2인게임");
	setColor(WHITE, 0);
	gotoxy(DETAIL - 8, DETAIL + 2);
	printf("이동     ←  →         D   G     ←  → ");
	gotoxy(DETAIL - 8, DETAIL + 3);
	printf("당기기     ↓             F         ↓ ");
	gotoxy(DETAIL - 8, DETAIL + 4);
	printf("발사    space bar         A          /");
	gotoxy(DETAIL - 5, DETAIL + 6);
	setColor(RED, 0);
	printf("메인화면으로 돌아가려면 esc를 누르세요.");

	nextButton();
	if (esc == 1) return;
	detailClear(7);

	// 아이템 설명
	gotoxy(DETAIL, DETAIL);
	setColor(GREEN, 0);
	printf("한 번에 12개 이상의 구슬을 떨어뜨리면");
	gotoxy(DETAIL, DETAIL + 1);
	setColor(SKYBLUE, 0);
	printf("랜덤으로 아이템을 획득합니다.");

	gotoxy(DETAIL - 8, DETAIL + 3);
	setColor(WHITE, 0);
	printf(" ↕ | 발사 지점 세로줄의 구슬이 쨍그랑!");
	gotoxy(DETAIL - 8, DETAIL + 4);
	printf(" ⇔ | 발사 지점 가로줄의 구슬이 쨍그랑!");
	gotoxy(DETAIL - 8, DETAIL + 5);
	printf(" ⊙ | 발사 지점 근방의 구슬이 쨍그랑!");

	gotoxy(DETAIL, DETAIL + 7);
	setColor(GREEN, 0);
	printf("보조선 도우미/대전모드 공격 아이템은");
	gotoxy(DETAIL, DETAIL + 8);
	setColor(SKYBLUE, 0);
	printf("게임에서 직접 확인하세요!");

	nextButton();
	if (esc == 1) return;
	detailClear(9);

	// 모드 설명
	gotoxy(DETAIL - 8, DETAIL);
	setColor(PINK, 0);
	printf("일반모드 | 구슬이 무제한으로 제공됩니다.");
	gotoxy(DETAIL - 8, DETAIL + 2);
	setColor(BLUE, 0);
	printf("제한모드 | 20개의 구슬만 발사할 수 있습니다.");
	gotoxy(DETAIL - 8, DETAIL + 4);
	setColor(PINK, 0);
	printf("대전모드 | 2인전용. 승부를 겨뤄보세요!");

	nextButton();
	if (esc == 1) return;
	detailClear(5);
}

void selectPlayer()
{
	optionClear(2);
	playingSong(LOBBY, FALSE);
	cursorView(1);

	gotoxy(OPTION_X, OPTION_Y);
	printf("1 PLAYER");
	gotoxy(OPTION_X, OPTION_Y + 2);
	printf("2 PLAYERS");

	players = upDownButton(2) + 1;
	player1 = 1;
	player2 = 0;

	if (players == 2) player2 = 1;
}

void selectMode()
{
	optionClear(2);

	gotoxy(OPTION_X, OPTION_Y);
	printf("NORMAL GAME");
	gotoxy(OPTION_X, OPTION_Y + 2);
	printf("30 BALLS GAME");

	if (players == 1) mode = upDownButton(2);

	else
	{
		gotoxy(OPTION_X, OPTION_Y + 4);
		printf("VS GAME");

		mode = upDownButton(3);
	}
}

void ranking()
{
	setColor(0, 0);
	playingSong(ELFO, FALSE);
	system("cls");
	
	printf("\n\n\n");
	setColor(SKYBLUE, 0);
	printf("      ___ _  _ ___ ___ __  ____    ____ _ ___\n");
	setColor(PINK, 0);
	printf("     | o ) |_|| o ) o ) /_/ o__＼ | o_)o | o_)\n");
	setColor(YELLOW, 0);
	printf("     |_O_)____/_O_)_O_)___＼___/  |_| |__|_|\n");

	for (int i = 1; i <= players; i++)
	{
		detailClear(4);
		gotoxy(0, DETAIL - 2);
		printf("                                                ");
		gotoxy(DETAIL - 3, DETAIL - 2);
		printf("PLAYER %d! YOUR POPPING SCORE IS %3d", i, scores[i]);

		int myRank = 0;
		int done = 0;
		FILE *f;
		
		switch (mode)
		{
		case 0:
			f = fopen("records/record_0.txt", "r");
			break;
		case 1:
			f = fopen("records/record_1.txt", "r");
			break;
		case 2:
			f = fopen("records/record_2.txt", "r");
			break;
		}

		int rank1Index = 0, rank2Index = 0;
		memset(rank1, 0, sizeof(rank1));
		memset(rank2, 0, sizeof(rank2));

		for (int j = 0; j < 10; j++)
		{
			char rname[10];
			int rscore, rrank;

			fscanf(f, "%d %d %s", &rrank, &rscore, rname);

			if (rscore >= scores[i])
			{
				rank1[rank1Index].rank = rrank;
				rank1[rank1Index].score = rscore;
				strcpy(rank1[rank1Index++].name, rname);
			}
			else
			{
				switch (done)
				{
				case 0:
					myRank = j + 1;
					done = 1;
					break;
				case 1:
					rank2[rank2Index].rank = rrank;
					rank2[rank2Index].score = rscore;
					strcpy(rank2[rank2Index++].name, rname);
					break;
				}
			}
		}
		fclose(f);

		if (myRank)
		{
			gotoxy(DETAIL - 7, DETAIL + 2);
			printf("축하합니다! %d위 랭커로 등극하셨습니다!\n", myRank);
			gotoxy(DETAIL - 7, DETAIL + 3);
			printf("이름을 한 자씩 입력하고 엔터를 누르세요.");

			char c;
			char name[4];
			memset(name, 0, sizeof(name));

			for (int j = 0; j < 3; j++)
			{
				int select = 65;
				gotoxy(DETAIL + 2 * j, DETAIL + 5);
				printf("%c", select);

				while (TRUE)
				{
					if (_kbhit())
					{
						c = _getch();
						if (c == ESC) return;
						if (c == ENT || c == SPC)
						{
							name[j] = select;
							playingSound(SELECT);
							break;
						}
						if (c == -32)
						{
							c = _getch();
							switch (c)
							{
							case UP:
								select--;
								if (select == 64) select = 90;
								playingSound(SHOOT);
								break;
							case DOWN:
								select++;
								if (select == 91) select = 65;
								playingSound(SHOOT);
								break;
							}
						}
					}
					gotoxy(DETAIL + 2 * j, DETAIL + 5);
					printf("%c", select);
				}
			}

			switch (mode)
			{
			case 0:
				f = fopen("records/record_0.txt", "w");
				break;
			case 1:
				f = fopen("records/record_1.txt", "w");
				break;
			case 2:
				f = fopen("records/record_2.txt", "w");
				break;
			}

			for (int j = 0; rank1[j].rank != 0; j++)
			{
				fprintf(f, "%d %d %s\n", rank1[j].rank, rank1[j].score, rank1[j].name);
			}

			fprintf(f, "%d %d %s\n", myRank, scores[i], name);

			for (int j = 0; rank2[j].rank != 0; j++)
			{
				fprintf(f, "%d %d %s\n", rank2[j].rank, rank2[j].score, rank2[j].name);
			}

			fclose(f);
		}
		else nextButton();
	}
	
	FILE* f;
	switch (mode)
	{
	case 0:
		f = fopen("records/record_0.txt", "r");
		break;
	case 1:
		f = fopen("records/record_1.txt", "r");
		break;
	case 2:
		f = fopen("records/record_2.txt", "r");
		break;
	}

	detailClear(6); 
	gotoxy(0, DETAIL - 2);
	printf("                                                ");

	gotoxy(DETAIL - 10, DETAIL - 2);
	for (int i = 0; i < 10; i++)
	{
		int rrank, rscore;
		char rname[10];
		fscanf(f, "%d %d %s\n", &rrank, &rscore, &rname);
		Sleep(500);
		printf("%12d위  |  %8s  | %8d점\n", rrank, rname, rscore);
	}
	Sleep(500);

	nextButton();
}