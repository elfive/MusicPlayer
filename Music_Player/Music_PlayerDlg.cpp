#include "stdafx.h"
#include "Music_Player.h"
#include "Music_PlayerDlg.h"
#include "afxdialogex.h"
#include "string"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMusic_PlayerDlg * pSelf;

CMusic_PlayerDlg::CMusic_PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MUSIC_PLAYER_DIALOG, pParent)
{
	pSelf = this;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusic_PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ctl_info, m_info);
	DDX_Control(pDX, ctl_Pitch_slider, m_Pitch_slider);
	DDX_Control(pDX, ctl_Rate_slider, m_Rate_slider);
	DDX_Control(pDX, ctl_Tempo_slider, m_Tempo_slider);
	DDX_Control(pDX, ctl_Volume_slider, m_Volume_slider);
	DDX_Control(pDX, ctl_Play, m_Play);
	DDX_Control(pDX, ctl_Stop, m_Stop);
	DDX_Control(pDX, ctl_BASS, m_BASS);
	DDX_Control(pDX, ctl_EQ1_slider, m_EQ1_slider);
	DDX_Control(pDX, ctl_EQ2_slider, m_EQ2_slider);
	DDX_Control(pDX, ctl_EQ3_slider, m_EQ3_slider);
	DDX_Control(pDX, ctl_EQ4_slider, m_EQ4_slider);
	DDX_Control(pDX, ctl_EQ5_slider, m_EQ5_slider);
	DDX_Control(pDX, ctl_EQ6_slider, m_EQ6_slider);
	DDX_Control(pDX, ctl_EQ7_slider, m_EQ7_slider);
	DDX_Control(pDX, ctl_EQ8_slider, m_EQ8_slider);
	DDX_Control(pDX, ctl_FileList, m_FileList);
	DDX_Control(pDX, ctl_EQ1_static, m_EQ1_static);
	DDX_Control(pDX, ctl_EQ2_static, m_EQ2_static);
	DDX_Control(pDX, ctl_EQ3_static, m_EQ3_static);
	DDX_Control(pDX, ctl_EQ4_static, m_EQ4_static);
	DDX_Control(pDX, ctl_EQ5_static, m_EQ5_static);
	DDX_Control(pDX, ctl_EQ6_static, m_EQ6_static);
	DDX_Control(pDX, ctl_EQ7_static, m_EQ7_static);
	DDX_Control(pDX, ctl_EQ8_static, m_EQ8_static);
	DDX_Control(pDX, ctl_FastForward, m_FastForward);
	DDX_Control(pDX, ctl_FastBackward, m_FastBackward);
}

BEGIN_MESSAGE_MAP(CMusic_PlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ctl_Play, &CMusic_PlayerDlg::Play)
	ON_BN_CLICKED(ctl_Stop, &CMusic_PlayerDlg::Stop)
	ON_BN_CLICKED(ctl_Reverse, &CMusic_PlayerDlg::OnReverse)
	ON_BN_CLICKED(ctl_SideCut, &CMusic_PlayerDlg::OnSideCut)
	ON_BN_CLICKED(ctl_BASS, &CMusic_PlayerDlg::BASS)
	ON_BN_CLICKED(ctl_Center, &CMusic_PlayerDlg::OnCenterCut)
	ON_BN_CLICKED(ctl_Reset_btn, &CMusic_PlayerDlg::Reset)
	ON_BN_CLICKED(ctl_ResetEQ_btn, &CMusic_PlayerDlg::ResetEQ)
	ON_BN_CLICKED(ctl_FastForward, &CMusic_PlayerDlg::OnFastForward)
	ON_BN_CLICKED(ctl_FastBackward, &CMusic_PlayerDlg::OnFastBackward)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Pitch_slider, &CMusic_PlayerDlg::OnPitchChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Rate_slider, &CMusic_PlayerDlg::OnRateChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Tempo_slider, &CMusic_PlayerDlg::OnTempoChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Volume_slider, &CMusic_PlayerDlg::OnVolumeChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ1_slider, &CMusic_PlayerDlg::OnEQ1Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ2_slider, &CMusic_PlayerDlg::OnEQ2Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ3_slider, &CMusic_PlayerDlg::OnEQ3Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ4_slider, &CMusic_PlayerDlg::OnEQ4Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ5_slider, &CMusic_PlayerDlg::OnEQ5Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ6_slider, &CMusic_PlayerDlg::OnEQ6Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ7_slider, &CMusic_PlayerDlg::OnEQ7Change)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_EQ8_slider, &CMusic_PlayerDlg::OnEQ8Change)
	ON_NOTIFY(NM_DBLCLK, ctl_FileList, &CMusic_PlayerDlg::OnFileListDblClick)

END_MESSAGE_MAP()

BOOL CMusic_PlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	Player.Init();

	InitCtl();
	return TRUE; 
}

void CMusic_PlayerDlg::InitPlayer()
{
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStopAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgPlayAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgEnterLoopAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgExitLoopAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgEnterVolumeSlideAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgExitVolumeSlideAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStreamBufferDoneAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStreamNeedMoreDataAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgNextSongAsync, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStop, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgPlay, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgEnterLoop, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgExitLoop, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgEnterVolumeSlide, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgExitVolumeSlide, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStreamBufferDone, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgStreamNeedMoreData, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgNextSong, NULL);
	Player.player->SetCallbackFunc(StopdPlayerCallback, (TCallbackMessage)MsgWaveBuffer, NULL);
}

void CMusic_PlayerDlg::InitCtl() 
{

	m_Pitch_slider.SetRange(-200, 0);
	m_Rate_slider.SetRange(-200, 0);
	m_Tempo_slider.SetRange(-200, 0);
	m_Volume_slider.SetRange(-100, 0);
	m_EQ1_slider.SetRange(-24000, 0);
	m_EQ1_slider.SetLineSize(250);
	m_EQ2_slider.SetRange(-24000, 0);
	m_EQ2_slider.SetLineSize(250);
	m_EQ3_slider.SetRange(-24000, 0);
	m_EQ3_slider.SetLineSize(250);
	m_EQ4_slider.SetRange(-24000, 0);
	m_EQ4_slider.SetLineSize(250);
	m_EQ5_slider.SetRange(-24000, 0);
	m_EQ5_slider.SetLineSize(250);
	m_EQ6_slider.SetRange(-24000, 0);
	m_EQ6_slider.SetLineSize(250);
	m_EQ7_slider.SetRange(-24000, 0);
	m_EQ7_slider.SetLineSize(250);
	m_EQ8_slider.SetRange(-24000, 0);
	m_EQ8_slider.SetLineSize(250);
	m_FileList.InsertColumn(0, L"File Path", 0, 100);
	InitCtlValue();
}

void CMusic_PlayerDlg::InitCtlValue() 
{
	
	m_Pitch_slider.SetPos(0 - pitch);
	m_Rate_slider.SetPos(0 - rate);
	m_Tempo_slider.SetPos(0 - tempo);
	m_Volume_slider.SetPos(0 - volume);
	SelectedItme = -1;
	m_FileList.DeleteAllItems();
	m_FileList.InsertItem(0, L"HeyJude.mp3");
	Player.player->AddFile("HeyJude.mp3", sfAutodetect);
	ResetEQ();
	bInitFinished = true;
	PrintInfo();
}

void CMusic_PlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMusic_PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMusic_PlayerDlg::Play()
{
	if(Player.GetStatus()!= PLAYING)
	{
		Player.Play();
		strStatus = L"Playing";
		m_Play.SetWindowText(L"Pause");
		m_FastForward.EnableWindow(TRUE);
		m_FastBackward.EnableWindow(TRUE);
	}
	else 
	{
		Player.Pause();
		strStatus = L"Paused";
		m_Play.SetWindowText(L"Paly");
	}
	PrintInfo();
}

void CMusic_PlayerDlg::Stop()
{
	Player.Stop();
	strStatus = L"Stopped";
	Reset();
	m_Play.SetWindowText(L"Paly");
	m_Play.EnableWindow(FALSE);
	m_Stop.EnableWindow(FALSE);
	m_FastForward.EnableWindow(FALSE);
	m_FastBackward.EnableWindow(FALSE);
	PrintInfo();
}

void CMusic_PlayerDlg::OnReverse()
{
	Player.Reverse();
	PrintInfo();
}

void CMusic_PlayerDlg::OnSideCut()
{
	Player.SideCut();
	PrintInfo();
}

void CMusic_PlayerDlg::OnCenterCut()
{
	Player.CenterCut();
	PrintInfo();
}

void CMusic_PlayerDlg::PrintInfo() 
{
	if (!bInitFinished) return;
	Player.GetStatus();

	CString strBass = (Player.Status.fEqualizer) ? L"Yes" : L"No";
	CString strReverse = (Player.Status.fReverse) ? L"Yes" : L"No";
	CString strSideCut = (Player.Status.fSideCut) ? L"Yes" : L"No";
	CString strCenterCut = (Player.Status.fVocalCut) ? L"Yes" : L"No";
	CString Info;
	Info.Format(L"Status：\t\t%s\nVolume：\t\t%d%%\nRate：\t\t\t%d%%\nTempo：\t\t%d%%\nPitch：\t\t\t%d%%\nEQ：\t\t\t%s\nReverse：\t\t%s\nSideCut：\t\t%s\nCenterCut：\t\t%s\n", strStatus, volume, rate, tempo, pitch, strBass, strReverse, strSideCut, strCenterCut);
	m_info.SetWindowText(Info);

	CString EQSetting = L"%.1fDb";
	CString EQ;
	EQ.Format(EQSetting, (double)EQEffect[0] / 1000);
	m_EQ1_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[1] / 1000);
	m_EQ2_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[2] / 1000);
	m_EQ3_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[3] / 1000);
	m_EQ4_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[4] / 1000);
	m_EQ5_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[5] / 1000);
	m_EQ6_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[6] / 1000);
	m_EQ7_static.SetWindowText(EQ);
	EQ.Format(EQSetting, (double)EQEffect[7] / 1000);
	m_EQ8_static.SetWindowText(EQ);
}

void CMusic_PlayerDlg::OnPitchChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (pitch == 0 - m_Pitch_slider.GetPos()) return;
	pitch = 0-m_Pitch_slider.GetPos();
	Player.SetPitch(pitch);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnTempoChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (tempo == 0 - m_Tempo_slider.GetPos()) return;
	tempo = 0-m_Tempo_slider.GetPos();
	Player.SetTempo(tempo);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnRateChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (rate == 0 - m_Rate_slider.GetPos()) return;
	rate = 0-m_Rate_slider.GetPos();
	Player.SetRate(rate);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnVolumeChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (volume == 0 - m_Volume_slider.GetPos()) return;
	volume = 0-m_Volume_slider.GetPos();
	Player.SetVolume(volume, volume);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::BASS() 
{
	EQEffect[0] = 6400;
	EQEffect[1] = 800;
	EQEffect[2] = -3200;
	EQEffect[3] = -6400;
	EQEffect[4] = -3200;
	EQEffect[5] = 800;
	EQEffect[6] = 6400;
	EQEffect[7] = 6400;
	SetEQPos();
}

void CMusic_PlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	wchar_t szFilePathName[_MAX_PATH + 1] = { 0 };
	int ListCount = m_FileList.GetItemCount();

	//得到文件个数      
	UINT nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	for (UINT i = 0; i < nNumOfFiles; i++) 
	{
		//得到文件名   
		DragQueryFile(hDropInfo, i, szFilePathName, _MAX_PATH);

		CString path = szFilePathName;
		m_FileList.InsertItem(ListCount + i, path);

		CT2CA pszConvertedAnsiString(path);
		string returnstring(pszConvertedAnsiString);

		Player.player->AddFile(returnstring.c_str(), sfAutodetect);
	}

	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CMusic_PlayerDlg::OnEQ1Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[0] != (-12000 - m_EQ1_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ2Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[1] != (-12000 - m_EQ2_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ3Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[2] != (-12000 - m_EQ3_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ4Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[3] != (-12000 - m_EQ4_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ5Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[4] != (-12000 - m_EQ5_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ6Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[5] != (-12000 - m_EQ6_slider.GetPos()))
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}
	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ7Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[6] != (-12000 - m_EQ7_slider.GetPos())) 
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}

	*pResult = 0;
}

void CMusic_PlayerDlg::OnEQ8Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	if (EQEffect[7] != (-12000 - m_EQ8_slider.GetPos())) 
	{
		if (!bSetEQPos)
			ApplyEQSettings();
	}

	*pResult = 0;
}

void CMusic_PlayerDlg::ApplyEQSettings()
{
	EQEffect[0] = (- 12000 - m_EQ1_slider.GetPos());
	EQEffect[1] = (- 12000 - m_EQ2_slider.GetPos());
	EQEffect[2] = (- 12000 - m_EQ3_slider.GetPos());
	EQEffect[3] = (- 12000 - m_EQ4_slider.GetPos());
	EQEffect[4] = (- 12000 - m_EQ5_slider.GetPos());
	EQEffect[5] = (- 12000 - m_EQ6_slider.GetPos());
	EQEffect[6] = (- 12000 - m_EQ7_slider.GetPos());
	EQEffect[7] = (- 12000 - m_EQ8_slider.GetPos());
	Player.SetEQ(EQEffect, 8);
	PrintInfo();
}

void CMusic_PlayerDlg::SetEQPos() 
{
	bSetEQPos = true;
	m_EQ1_slider.SetPos(0 - (EQEffect[0] + 12000));
	m_EQ2_slider.SetPos(0 - (EQEffect[1] + 12000));
	m_EQ3_slider.SetPos(0 - (EQEffect[2] + 12000));
	m_EQ4_slider.SetPos(0 - (EQEffect[3] + 12000));
	m_EQ5_slider.SetPos(0 - (EQEffect[4] + 12000));
	m_EQ6_slider.SetPos(0 - (EQEffect[5] + 12000));
	m_EQ7_slider.SetPos(0 - (EQEffect[6] + 12000));
	m_EQ8_slider.SetPos(0 - (EQEffect[7] + 12000));
	bSetEQPos = false;
	ApplyEQSettings();

}

void CMusic_PlayerDlg::Reset() 
{
	InitCtlValue();
	unsigned int volume = 100;
	CString strStatus = L"Paused";
	m_Play.SetWindowText(L"Play");
	m_Play.EnableWindow(FALSE);
	m_Stop.EnableWindow(FALSE);
	m_FastForward.EnableWindow(FALSE);
	m_FastBackward.EnableWindow(FALSE);
	Player.Init();
}

void CMusic_PlayerDlg::ResetEQ() 
{
	for (int i = 0; i < 8; i++)
	{
		EQEffect[i] = 0;
	}
	SetEQPos();
}

int __stdcall CMusic_PlayerDlg::StopdPlayerCallback(void* instance, void *user_data, TCallbackMessage message, unsigned int param1, unsigned int param2)
{
	int msg = message;
	int Count = pSelf->m_FileList.GetItemCount();
	if (Count!= 0)
	{
		if (pSelf->SelectedItme == Count)
		{ 
			pSelf->SelectedItme = 0; 
		}
		else 
		{
			pSelf->SelectedItme++;
		}
		pSelf->m_FileList.SetItemState(pSelf->SelectedItme, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		pSelf->PlayListItem(pSelf->SelectedItme);
	}
	return 0;
}

void CMusic_PlayerDlg::OnFileListDblClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int SelItemIndex = pNMLV->iItem;
	if (SelItemIndex == -1) return;
	PlayListItem(SelItemIndex);
	m_Stop.EnableWindow(TRUE);
	m_FastForward.EnableWindow(TRUE);
	m_FastBackward.EnableWindow(TRUE);
	*pResult = 0;
}

void CMusic_PlayerDlg::PlayListItem(int index) 
{
	CString path = m_FileList.GetItemText(index, 0);
	CT2CA pszConvertedAnsiString(path);
	string strPath(pszConvertedAnsiString);
	Player.Stop();
	Player.Open(strPath.c_str());
	Play();
	m_Play.EnableWindow(TRUE);
}

void CMusic_PlayerDlg::OnFastForward()
{
	Player.FastForward();
}

void CMusic_PlayerDlg::OnFastBackward()
{
	Player.FastBackward();
}
