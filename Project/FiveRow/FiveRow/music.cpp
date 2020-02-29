#include "music.h"

void initMusic()
{
	
	mciSendStringA("open bgm/bkmusic.mp3 alias bk", NULL, 0,NULL);
	mciSendStringA("open bgm/failure.mp3 alias lose", NULL, 0, NULL);
	mciSendStringA("open bgm/win.wav alias win", NULL, 0, NULL);
	mciSendStringA("open bgm/put.wav alias put", NULL, 0, NULL);
}

void closeMusic()
{
	mciSendStringA("close bk", NULL, 0, NULL);
	mciSendStringA("close lose", NULL, 0, NULL);
	mciSendStringA("close win", NULL, 0, NULL);
	mciSendStringA("close put", NULL, 0, NULL);
}

void playPutchessMusic()
{
	if (g_setting.bkEffect) {
		mciSendStringA("play put from 0", NULL, 0, NULL);
	}
}

void playBkMusic()
{
	if (g_setting.bkMusic) {
		mciSendStringA("play bk repeat", NULL, 0, NULL);
	}
}

void stopBkMusic()
{
	mciSendStringA("stop bk", NULL, 0, NULL);
}

void playWinMusic()
{
	if (g_setting.bkEffect) {
		mciSendStringA("play win from 0", NULL, 0, NULL);
	}
}

void playLoseMusic()
{
	if (g_setting.bkEffect) {
		mciSendStringA("play lose from 0", NULL, 0, NULL);
	}
}

void updateBkMusic()
{
	if (g_setting.bkMusic) {
		playBkMusic();
	}
	else {
		stopBkMusic();
	}
}





