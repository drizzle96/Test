# include "main.h"

void initGame()
{
	cursorView(0);

	memset(scores, 0, sizeof(scores));
	remains[1] = remains[2] = 20;
	memset(helps, 0, sizeof(helps));
	memset(items, 0, sizeof(items));

	items[1][0] = items[2][0] = 1;
	esc = 0;
	dir1 = dir2 = 5;
	nextLine1 = nextLine2 = 3000;
	balls = 3;
	shoot1 = shoot2 = 0;
}

void initTimer()
{
	TIME = clock();
	TIME1 = clock();
	TIME2 = clock();
	DUR = clock();
	HELP1 = clock();
	HELP2 = clock();
}

void game()
{
	initTimer();
	playingSong(MAIN, TRUE);

	while (player1 + player2 != 0)
	{
		if (_kbhit())
		{
			char c = _getch();

			if (c == ESC)
			{
				esc = 1;
				playingSound(SELECT);
				return;
			}

			if (players == 1)
			{
				if (c == SPC)
				{
					playingSound(SHOOT);
					shoot1 = 1;
					ball[1].x = dir1;
				}

				if (c == -32)
				{
					c = _getch();

					switch (c)
					{
					case LEFT:
						if (dir1 > 1 && board_1p[13][dir1 - 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1--;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
							playingSound(SHOOT);
						}
						break;

					case RIGHT:
						if (dir1 < 9 && board_1p[13][dir1 + 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1++;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
							playingSound(SHOOT);
						}
						break;

					case DOWN:
						down(1);
						TIME1 = clock();
						break;
					}
				}
			}
			else
			{
				if (player1 > 0)
				{
					if (c == 'D' || c == 'd' || c == 'ㅇ')
					{
						if (!items[1][4] && dir1 >= 1 && board_1p[13][dir1 - 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1--;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
						}
						if (items[1][4] && dir1 <= 9 && board_1p[13][dir1 + 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1++;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
						}
					}

					else if (c == 'G' || c == 'g' || c == 'ㅎ')
					{
						if (!items[1][4] && dir1 <= 9 && board_1p[13][dir1 + 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1++;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
						}
						if (items[1][4] && dir1 >= 1 && board_1p[13][dir1 - 1] == 0)
						{
							board_1p[13][dir1] = board_1p[12][dir1] = 0;
							dir1--;
							board_1p[13][dir1] = ARROW;
							board_1p[12][dir1] = ball[1].color;
						}
					}

					else if (c == 'A' || c == 'a' || c == 'ㅎ')
					{
						shoot1 = 1;
						playingSound(2);
						ball[1].x = dir1;
						playingSound(SHOOT);
					}

					else if (c == 'F' || c == 'f' || c == 'ㄹ')
					{
						down(1);
						TIME1 = clock();
					}
				}

				if (player2 > 0)
				{
					if (c == '/')
					{
						shoot2 = 1;
						playingSound(SHOOT);
						ball[2].x = dir2;
					}

					if (c == -32)
					{
						c = _getch();

						if (c == LEFT)
						{
							if (!items[2][4] && dir2 >= 1 && board_2p[13][dir2 - 1] == 0)
							{
								board_2p[13][dir2] = board_2p[12][dir2] = 0;
								dir2--;
								board_2p[13][dir2] = ARROW;
								board_2p[12][dir2] = ball[2].color;
							}
							if (items[2][4] && dir2 <= 9 && board_2p[13][dir2 + 1] == 0)
							{
								board_2p[13][dir2] = board_2p[12][dir2] = 0;
								dir2++;
								board_2p[13][dir2] = ARROW;
								board_2p[12][dir2] = ball[2].color;
							}
						}

						if (c == RIGHT)
						{
							if (!items[2][4] && dir2 <= 9 && board_2p[13][dir2 + 1] == 0)
							{
								board_2p[13][dir2] = board_2p[12][dir2] = 0;
								dir2++;
								board_2p[13][dir2] = ARROW;
								board_2p[12][dir2] = ball[2].color;
							}
							if (items[2][4] && dir2 >= 1 && board_2p[13][dir2 - 1] == 0)
							{
								board_2p[13][dir2] = board_2p[12][dir2] = 0;
								dir2--;
								board_2p[13][dir2] = ARROW;
								board_2p[12][dir2] = ball[2].color;
							}
						}

						if (c==DOWN)
						{
							down(2);
							TIME2 = clock();
						}
					}
				}
			}
		}
		
		if (clock() - TIME > TIMING)
		{
			// 원래 여기서 죽었는지 체크
			if (shoot1 == 1) move(1);
			if (shoot2 == 1) move(2);

			if (shoot1 == 0 && items[1][0])
			{
				switch (helpToggle1)
				{
				case 0:
					helpLine(1);
					gotoxy(0, 0);
					helpToggle1 = 1;
					break;
				case 1:
					deleteHelpLine(1);
					helpToggle1 = 0;
					break;
				}
			}
			if (shoot2 == 0 && items[2][0])
			{
				switch (helpToggle2)
				{
				case 0:
					helpLine(2);
					gotoxy(28, 0);
					helpToggle2 = 1;
					break;
				case 1:
					deleteHelpLine(2);
					helpToggle2 = 0;
					break;
				}
			}

			if (player1 > 0)
			{
				draw(1);
				score(1);
			}
			if (player2 > 0)
			{
				draw(2);
				score(2);
			}


			if (mode == LIMITED_GAME && remains[1] == 0)
			{
				player1 = 0;
				gameOver(1);
				playingSound(END);
				draw(1);
				remains[1] = -1;
			}

			if (mode == LIMITED_GAME && remains[2] == 0)
			{
				player2 = 0;
				gameOver(2);
				playingSound(END);
				draw(2);
				remains[2] = -1;
			}

			if (player1 && deadCheck(1))
			{
				player1 = 0;
				gameOver(1);
				playingSound(END);
				draw(1);
			}
			if (player2 && deadCheck(2))
			{
				player2 = 0;
				gameOver(2);
				playingSound(END);
				draw(2);
			}

			TIME = clock();
			//}

			if (player1 && clock() - TIME1 > nextLine1)
			{
				down(1);
				TIME1 = clock();
			}

			if (player2 && clock() - TIME2 > nextLine2)
			{
				down(2);
				TIME2 = clock();
			}

			if (clock() - DUR > NEXTBALL && balls < 15)
			{
				balls++;
				DUR = clock();
				playingSound(MORE);
			}

			if (clock() - HELP1 > HELPTIME && items[1][0])
			{
				items[1][0] = 0;
				deleteHelpLine(1);
			}

			if (clock() - HELP2 > HELPTIME && items[2][0])
			{
				items[2][0] = 0;
				deleteHelpLine(2);
			}

			if (clock() - REVERSE1 > REVETIME && items[2][4])
			{
				items[2][4] = 0;
			}

			if (clock() - REVERSE2 > REVETIME && items[1][4])
			{
				items[1][4] = 0;
			}

			if (clock() - MASK1 > MASKTIME && items[2][6])
			{
				items[2][6] = 0;
				draw(2);
			}

			if (clock() - MASK2 > MASKTIME && items[1][6])
			{
				items[1][6] = 0;
				draw(1);
			}
		}
	}
	Sleep(2000);
	nextButton();
}

void move(int playerNo)
{
	if (playerNo == 1)
	{
		int y = ball[1].y;
		int x = ball[1].x;
		while (board_1p[y - 1][x] == 0 || board_1p[y - 1][x] == HELPLINE)
		{
			if (--y == 0) break;
		}
		
		board_1p[y][x] = ball[1].color;
		
		if (y <= 11)
		{
			ball[1].y = y;
			shoot1 = 0;
			check(1);

			initBall(1);

			for (int i = 1; i <= 3; i++)
			{
				if (items[1][i])
				{
					next[1].color = -10 * i;
					items[1][i] = 0;
					gotoxy(SCORE_1P_X + 16, SCORE_Y);
					switch (next[1].color)
					{
					case COLBOMB:
						setColor(15, 0);
						printf("↕");
						break;
					case ROWBOMB:
						setColor(15, 0);
						printf("⇔");
						break;
					case BOXBOMB:
						setColor(15, 0);
						printf("⊙");
						break;
					}
				}
			}

			if (mode == 1)
			{
				remains[1]--;
				gotoxy(SCORE_1P_X + 6, SCORE_Y + 1);
				setColor(WHITE, 0);
				printf("%4d", remains[1]);
			}
		}
		else
		{
			player1 = 0;
			gameOver(1);
			playingSound(END);
		}
	}
	else
	{
		int y = ball[2].y;
		int x = ball[2].x;
		while (board_2p[y - 1][x] == 0 || board_2p[y - 1][x] == HELPLINE)
		{
			if (--y == 0) break;
		}

		board_2p[y][x] = ball[2].color;

		if (y <= 11)
		{
			ball[2].y = y;
			shoot2 = 0;
			check(2);

			initBall(2);

			for (int i = 1; i <= 3; i++)
			{
				if (items[2][i])
				{
					next[2].color = -10 * i;
					items[2][i] = 0;
					gotoxy(SCORE_2P_X + 16, SCORE_Y);
					switch (next[2].color)
					{
					case COLBOMB:
						setColor(15, 0);
						printf("↕");
						break;
					case ROWBOMB:
						setColor(15, 0);
						printf("⇔");
						break;
					case BOXBOMB:
						setColor(15, 0);
						printf("⊙");
						break;
					}
				}
			}

			if (mode == 1)
			{
				remains[2]--;
				gotoxy(SCORE_2P_X + 6, SCORE_Y + 1);
				setColor(WHITE, 0);
				printf("%4d", remains[2]);
			}
		}
		else
		{
			player2 = 0;
			gameOver(END);
			playingSound(4);
		}
	}
}

void draw(int playerNo)
{
	for (int i = 0; i < 15; i++)
	{
		if (playerNo == 1) gotoxy(0, i);
		else gotoxy(28, i);
	
		for (int j = 0; j < 11; j++)
		{
			int input = 0;
			if (playerNo == 1) input = board_1p[i][j];
			else input = board_2p[i][j];

			switch (input)
			{
			case COLBOMB:
				setColor(15, 0);
				printf("↕");
				break;
			case ROWBOMB:
				setColor(15, 0);
				printf("⇔");
				break;
			case BOXBOMB:
				setColor(15, 0);
				printf("⊙");
				break;
			case WALL:
				setColor(6, 0);
				printf("▩");
				break;
			case EMPTY:
				setColor(15, 0);
				printf("  ");
				break;
			case HELPLINE:
				setColor(15, 0);
				printf("↑");
				break;
			case ARROW:
				setColor(6, 0);
				printf("▲");
				break;
			default:
				if (items[playerNo][6]) setColor(WHITE, 0);
				else if (input < 20) setColor(input, 0);
				else setColor(input - 20, input - 20);
				printf("●");
				break;
			}
		}
		printf("\n");
	}
	if (player1 == 0)
	{
		setColor(RED, WHITE);
		gotoxy(SCORE_1P_X + 5, BALL_Y - 5);
		printf("GAME OVER");
	}
	if (players == 2 && player2 == 0)
	{
		setColor(RED, WHITE);
		gotoxy(SCORE_2P_X + 5, BALL_Y - 5);
		printf("GAME OVER");
	}
}

void score(int playerNo)
{
	int cnt = 0;

	if (playerNo == 1)
	{
		for (int i = 11; i >= 0; i--)
		{
			for (int j = 1; j < 10; j++)
			{
				if (20 <= board_1p[i][j] && board_1p[i][j] != 1000)
				{
					board_1p[i][j] = 0;
					cnt++;

					for (int k = i + 1; k < 11; k++)
					{
						if (board_1p[k][j] != 0)
						{
							board_1p[k][j] = 0;
							cnt++;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 11; i >= 0; i--)
		{
			for (int j = 1; j < 10; j++)
			{
				if (20 <= board_2p[i][j] && board_2p[i][j] != 1000)
				{
					board_2p[i][j] = 0;
					cnt++;

					for (int k = i + 1; k < 11; k++)
					{
						if (board_2p[k][j] != 0)
						{
							board_2p[k][j] = 0;
							cnt++;
						}
					}
				}
			}
		}
	}

	if (cnt >= 12)
	{
		int itemNo = 0;
		
		if (mode == VSMODE_GAME) itemNo = clock() % 7;
		else itemNo = rand() % 4;

		if (itemNo == 6 || itemNo == 4)
		{
			if (playerNo == 1) items[2][itemNo] = 1;
			else items[1][itemNo] = 1;
		}
		else items[playerNo][itemNo] = 1;

		switch (itemNo)
		{
		case 0:
			if (playerNo == 1) HELP1 = clock();
			else HELP2 = clock();
			playingSound(SHA);
			break;
		case 4:
			if (playerNo == 1)
			{
				REVERSE1 = clock();
			}
			else
			{
				REVERSE2 = clock();
			}
			playingSound(GUN);
			break;
		case 5:
			swapBoard();
			playingSound(CHANGE);
			items[playerNo][5] = 0;
			break;
		case 6:
			if (playerNo == 1) MASK1 = clock();
			else MASK2 = clock();
			playingSound(ATK);
			break;
		}
	}

	if (cnt >= 5) cnt *= 1.2;
	else if (cnt >= 10) cnt *= 1.4;
	else if (cnt >= 15) cnt *= 1.6;
	else if (cnt >= 20) cnt *= 1.8;
	else if (cnt >= 25) cnt *= 2;

	scores[playerNo] += cnt;

	switch (playerNo)
	{
	case 1:
		setColor(WHITE, 0);
		gotoxy(SCORE_1P_X + 5, SCORE_Y);
		printf("%5d", scores[playerNo]);
		break;
	case 2:
		setColor(WHITE, 0);
		gotoxy(SCORE_2P_X + 5, SCORE_Y);
		printf("%5d", scores[playerNo]);
		break;
	}
}

int deadCheck(int playerNo)
{
	if (playerNo == 1)
	{
		for (int i = 1; i < 10; i++)
		{
			if (3 <= board_1p[11][i] && board_1p[11][i] <= 20) return 1;
		}
	}
	if (playerNo == 2)
	{
		for (int i = 1; i < 10; i++)
		{
			if (3 <= board_2p[11][i] && board_2p[11][i] <= 20) return 1;
		}
	}
	return 0;
}

void gameOver(int playerNo)
{
	if (playerNo == 1)
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				board_1p[i][j] = 0;
			}
		}
		
	}
	else
	{
		for (int i = 0; i < 14; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				board_2p[i][j] = 0;
			}
		}
	}
}