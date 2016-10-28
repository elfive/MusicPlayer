#pragma once
#include "Libzplay\libzplay.h"
using namespace libZPlay;

enum
{
	PLAYING = 0,
	PAUSE = 1,
	STOP = 2
};

class CMusicPlayer
{
public:


	CMusicPlayer();
	~CMusicPlayer();

	bool Init();
	bool Open(const char * FilePath);
	bool Play();
	bool Pause();
	bool Resume();
	bool Stop();
	bool FastForward(unsigned int JumpTime = 5);
	bool FastBackward(unsigned int JumpTime = 5);
	void ChanegVolume(int Left = 5, int Right = 5);
	void SetVolume(unsigned int Left, unsigned int Right);
	void GetVolume(unsigned int * Left, unsigned int * Right);

	void SideCut();
	void CenterCut();
	void HigherRate(int rate = 5);
	void LowerRate(int rate = 5);
	void HigherTempo(int tempo = 5);
	void LowerTempo(int tempo = 5);
	void HigherPitch(int pitch = 5);
	void SetPitch(int pitch);
	void SetTempo(int tempo);
	void SetRate(int rate);
	void LowerPitch(int pitch = 5);
	void Reverse();
	bool isPlaying();
	int GetStatus();

	void SetEQ(int band0, int band1, int band2, int band3, int band4, int band5, int band6, int band7);
	void SetEQ(int band[8]);
	void RestoreEQ(int band[8]);

private:
	ZPlay * player;
	TID3InfoEx id3_info;
	TStreamInfo pInfo;
	TStreamStatus status;

	int lVolume = 100;		//左声道音量百分比
	int rVolume = 100;		//右声道音量百分比

	bool isInited;
	bool isOpenedFile;
	bool isGetID3Info;
	bool isSideCut;
	bool isCenterCut;
	bool isReverse;
	int nRate;
	int nTempo;
	int nPitch;
	bool fEq;
}; 

