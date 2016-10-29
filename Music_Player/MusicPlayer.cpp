#include "stdafx.h"
#include "MusicPlayer.h"

CMusicPlayer::CMusicPlayer()
{
	isOpenedFile = false;
	isGetID3Info = false;
	isInited = false;
	nRate = 100;
	nTempo = 100;
	nPitch = 100;
}

CMusicPlayer::~CMusicPlayer()
{
	if(isInited)
		player->Release();
}

bool CMusicPlayer::Init()
{
	if (player != NULL)
		player->Release();
	player = CreateZPlay();
	if (player == 0)
	{
		OutputDebugString(L"Can't create class instance !\n");
		return false;
	}

	int ver = player->GetVersion();
	// check if we have version 1.90 and above ( 1.90 if PF (pattent free) version, 2.00 version is full version
	if (ver < 190)
	{
		OutputDebugString(L"Need library version 2.00 and above !\n");
		player->Release();
		return false;
	}

	CString VerInfo;
	VerInfo.Format(L"libZPlay v.%i.%02i\n", ver / 100, ver % 100);
	OutputDebugString(VerInfo);

	int eq_points[7] = { 100, 400, 1000, 3000, 5000, 10000, 15000 };
	CreateEQPoint(eq_points, 7);
	player->EnableEqualizer(false);
	isInited = true;


	return true;
}

bool CMusicPlayer::Open(const char * FilePath)
{
	if (player->OpenFile(FilePath, sfAutodetect) == 0)
	{
		CString ErrMsg;
		ErrMsg.Format(L"Can't open media file !\nErr: %s\n", player->GetError());
		OutputDebugString(ErrMsg);
		isOpenedFile = false;
		return false;
	}
	isOpenedFile = true;

	if (player->LoadID3Ex(&id3_info, 1))
	{
		printf("Title:   %s\r\n", id3_info.Title);
		printf("Artist:  %s\r\n", id3_info.Artist);
		printf("Album:   %s\r\n", id3_info.Album);
		printf("Year:    %s\r\n", id3_info.Year);
		printf("Comment: %s\r\n", id3_info.Comment);
		printf("Genre:   %s\r\n", id3_info.Genre);
		printf("Track:   %s\r\n", id3_info.TrackNum);
		printf("Album Artist :  %s\r\n", id3_info.AlbumArtist);
		printf("Composer:  %s\r\n", id3_info.Composer);
		printf("Original:  %s\r\n", id3_info.OriginalArtist);
		printf("Copyright: %s\r\n", id3_info.Copyright);
		printf("URL:       %s\r\n", id3_info.URL);
		printf("Encoder:   %s\r\n", id3_info.Encoder);
		printf("Publisher: %s\r\n", id3_info.Publisher);
		printf("BPM:       %u\r\n", id3_info.BPM);
		printf("MIME:      %s\r\n", id3_info.Picture.MIMEType);
		printf("TYPE:      %u\r\n", id3_info.Picture.PictureType);
		printf("Desc:      %s\r\n", id3_info.Picture.Description);
		printf("Size:      %u\r\n", id3_info.Picture.PictureDataSize);

		//player->DrawBitmapToHWND(NULL, 0, 0, 0, 0, id3_info.Picture.hBitmap);
		isGetID3Info = true;
	}
	else
	{
		isGetID3Info = false;
		OutputDebugString(L"No ID3 data.\n");
	}

	player->GetStreamInfo(&pInfo);
	char *sVbr = "CBR";
	if (pInfo.VBR)
		sVbr = "VBR";

	printf("\r\n%s %i Hz %s  Channel: %u  Length: %02i:%02i:%02i:%02i\r\n\r\n",
		pInfo.Description,
		pInfo.SamplingRate,
		sVbr,
		pInfo.ChannelNumber,
		pInfo.Length.hms.hour,
		pInfo.Length.hms.minute,
		pInfo.Length.hms.second,
		pInfo.Length.hms.millisecond);


	return true;
}

bool CMusicPlayer::Play() 
{
	if (!isOpenedFile) return false;
	
	player->GetStatus(&Status);
	if (Status.fPlay) return true;

	if (player->Play() == 0) 
	{
		CString ErrMsg;
		ErrMsg.Format(L"Error during play\nErr:%s\n", player->GetError());
		OutputDebugString(ErrMsg);
		return false;
	}
	return true;
}

bool CMusicPlayer::Pause() 
{
	if (!isOpenedFile) return false;

	player->GetStatus(&Status);
	if (!Status.fPlay) return true;

	player->Pause();
	return true;
}

bool CMusicPlayer::Resume() 
{
	if (!isOpenedFile) return false;

	player->GetStatus(&Status);
	if (Status.fPlay) return true;

	player->Resume();
	return true;
}

bool CMusicPlayer::Stop() 
{
	if (!isOpenedFile) return true;
	player->Stop();
	isOpenedFile = false;
	return true;
}

bool CMusicPlayer::FastForward(unsigned int JumpTime) 
{
	if (!isOpenedFile) return false;
	TStreamTime pTime;
	pTime.sec = JumpTime;
	player->Seek(tfSecond, &pTime, smFromCurrentForward);
	return true;
}

bool CMusicPlayer::FastBackward(unsigned int JumpTime)
{
	if (!isOpenedFile) return false;
	TStreamTime pTime;
	pTime.sec = JumpTime;
	player->Seek(tfSecond, &pTime, smFromCurrentBackward);
	return true;
}

void CMusicPlayer::ChanegVolume(int Left,int Right) 
{
	if (lVolume > 100 - Left)
		lVolume = 100;
	else if (lVolume < 0 - Left)
		lVolume = 0;
	else
		lVolume += Left;

	if (rVolume > 100 - Right)
		rVolume = 100;
	else if (rVolume < 0 - Right)
		rVolume = 0;
	else
		rVolume += Right;

	player->SetMasterVolume(lVolume, rVolume);
}

void CMusicPlayer::SetVolume(unsigned int Left, unsigned int Right) 
{
	if (Left <= 100 && Left >= 0 && Right <= 100 && Right >= 0)
		player->SetMasterVolume(Left, Right);
	return;
}

void CMusicPlayer::GetVolume(unsigned int * Left, unsigned int * Right)
{
	player->GetMasterVolume(Left, Right);
	return;
}

//消除伴奏
void CMusicPlayer::SideCut() 
{
	isSideCut = !isSideCut;
	player->StereoCut(isSideCut, 1, 0);
	isCenterCut = false;
}

//消除人声
void CMusicPlayer::CenterCut() 
{
	isCenterCut = !isCenterCut;
	player->StereoCut(isCenterCut, 0, 0);
	isSideCut = false;
}

//速率
void CMusicPlayer::HigherRate(int rate) 
{
	nRate += rate;
	player->SetRate(nRate);
}

//速率
void CMusicPlayer::LowerRate(int rate)
{
	nRate -= rate;
	if (nRate < 0)
		nRate = 0;
	player->SetRate(nRate);
}

//节拍
void CMusicPlayer::HigherTempo(int tempo) 
{
	nTempo += tempo;
	player->SetTempo(nTempo);
}

//节拍
void CMusicPlayer::LowerTempo(int tempo)
{
	nTempo -= tempo;
	if (nTempo < 0)
		nTempo = 0;
	player->SetTempo(nTempo);
}

//音调
void CMusicPlayer::HigherPitch(int pitch)
{
	nPitch += pitch;
	player->SetPitch(nPitch);
}

//音调
void CMusicPlayer::LowerPitch(int pitch)
{
	nPitch -= pitch;
	if (nPitch < 0)
		nPitch = 0;
	player->SetTempo(nPitch);
}

void CMusicPlayer::SetPitch(int pitch)
{
	player->SetPitch(pitch);
}

void CMusicPlayer::SetTempo(int tempo)
{
	player->SetTempo(tempo);
}

void CMusicPlayer::SetRate(int rate)
{
	player->SetRate(rate);
}

//反转
void CMusicPlayer::Reverse()
{
	isReverse = !isReverse;

	if (player->ReverseMode(isReverse) == 0)
	{
		CString ErrMsg = L"Error: %s\n";
		ErrMsg.Format(ErrMsg, player->GetError());
		OutputDebugString(ErrMsg);
		isReverse = false;
	}
}

bool CMusicPlayer::isPlaying() 
{
	player->GetStatus(&Status);
	if (Status.fPlay) return true;
	return false;
}

int CMusicPlayer::GetStatus()
{
	player->GetStatus(&Status);
	if (Status.fPlay) return PLAYING;
	if (Status.fPause) return PAUSE;
	return STOP;
}

void CMusicPlayer::CreateEQPoint(int EQPoint[], int PointCount)
{
	player->SetEqualizerPoints(EQPoint, PointCount);
	PreviousBandCount = PointCount + 1;
}

void CMusicPlayer::SetEQ(const int band[],int bandCount)
{
	if (PreviousBandCount != bandCount) return;
	for (int i = 0; i < bandCount; i++)
	{
		player->SetEqualizerBandGain(i, band[i] - PreviousEQEffect[i]);
		PreviousEQEffect[i] = band[i];
	}
	player->EnableEqualizer(true);
}

void CMusicPlayer::ResetEQ() 
{
	for (int i = 0; i < PreviousBandCount; i++)
	{
		player->SetEqualizerBandGain(i, 0 - PreviousEQEffect[i]);
		PreviousEQEffect[i] = 0;
	}
	player->EnableEqualizer(false);
}
