#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

int song, dwID;
char* songs[13];

void initSong();

MCI_OPEN_PARMS openSong;
MCI_PLAY_PARMS playSong;

void playingSound(int soundNo);

void playingSong(int songNo, int loop);

void stopSong();
