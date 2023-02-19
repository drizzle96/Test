# include "main.h"

void initSong()
{
	songs[0] = "sounds/000.wav";
	songs[1] = "sounds/001.wav";
	songs[2] = "sounds/002.wav";
	songs[3] = "sounds/003.wav";
	songs[4] = "sounds/004.wav";
	songs[5] = "sounds/005.wav";
	songs[6] = "sounds/006.wav";
	songs[7] = "sounds/007.wav";
	songs[8] = "sounds/008.wav";
	songs[9] = "sounds/009.wav";
	songs[10] = "sounds/010.wav";
	songs[11] = "sounds/011.wav";
	songs[12] = "sounds/012.wav";
}

void playingSound(int songNo)
{
	PlaySound(TEXT(songs[songNo]), NULL, SND_ASYNC);
}

void playingSong(int songNo, int loop)
{
	stopSong();
	openSong.lpstrElementName = songs[songNo];
	openSong.lpstrDeviceType = "waveaudio";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openSong);
	dwID = openSong.wDeviceID;
	if (loop == TRUE) mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&playSong);
	else mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&playSong);
}

void stopSong()
{
	dwID = openSong.wDeviceID;
	mciSendCommand(dwID, MCI_CLOSE, 0, NULL);
}