# include "main.h"

void main()
{
	system("mode con cols=50 lines=20");
	initSong();

	while (1)
	{
		int nextStep = title();

		if (esc == TRUE)
		{
			esc = 0;
			continue;
		}

		if (nextStep == HOWTO)
		{
			howto();
			if (esc == TRUE) esc = 0;
			continue;
		}

		selectPlayer();
		if (esc == TRUE)
		{
			esc = 0;
			continue;
		}

		selectMode();
		if (esc == TRUE)
		{
			esc = 0;
			continue;
		}

		system("cls");
		initGame();
		initBoard();
		initBall(1);

		if (players == 2) initBall(2);
		game();

		if (esc == TRUE)
		{
			esc = 0;
			continue;
		}

		ranking();
		if (esc == TRUE) esc = 0;
	}
}