#include "stdafx.h"
#include "Music_Player.h"
#include "Music_PlayerDlg.h"
#include "afxdialogex.h"
#include "string"

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMusic_PlayerDlg::CMusic_PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MUSIC_PLAYER_DIALOG, pParent)
{
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
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Pitch_slider, &CMusic_PlayerDlg::OnPitchChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Rate_slider, &CMusic_PlayerDlg::OnRateChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Tempo_slider, &CMusic_PlayerDlg::OnTempoChange)
	ON_NOTIFY(NM_CUSTOMDRAW, ctl_Volume_slider, &CMusic_PlayerDlg::OnVolumeChange)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

BOOL CMusic_PlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	Player.Init();
	Player.Open("HeyJude.mp3");

	InitCtl();
	return TRUE; 
}

void CMusic_PlayerDlg::InitCtl() 
{

	m_Pitch_slider.SetRange(-200, 0);
	m_Pitch_slider.SetPos(0-pitch);
	m_Rate_slider.SetRange(-200, 0);
	m_Rate_slider.SetPos(0-rate);
	m_Tempo_slider.SetRange(-200, 0);
	m_Tempo_slider.SetPos(0-tempo);
	m_Volume_slider.SetRange(-100, 0);
	m_Volume_slider.SetPos(0-volume);
	
	PrintInfo();
}

void CMusic_PlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

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
		strStatus = L"���ڲ���";
		m_Play.SetWindowText(L"��ͣ");
	}
	else 
	{
		Player.Pause();
		strStatus = L"������ͣ";
		m_Play.SetWindowText(L"����");
	}
	PrintInfo();
}

void CMusic_PlayerDlg::Stop()
{
	if (Player.GetStatus() != STOP) 
	{
		Player.Stop();
		strStatus = L"�Ѿ�ֹͣ";
		m_Stop.SetWindowText(L"��");
	}
	else 
	{
		Player.Open("HeyJude.mp3");
		strStatus = L"������ͣ";
		m_Stop.SetWindowText(L"ֹͣ");
	}
	m_Play.SetWindowText(L"����");
	PrintInfo();
}

void CMusic_PlayerDlg::OnReverse()
{
	isReverse = !isReverse;
	Player.Reverse();
	PrintInfo();
}

void CMusic_PlayerDlg::OnSideCut()
{
	isSideCut = true;
	isCenterCut = false;
	Player.SideCut();
	PrintInfo();
}

void CMusic_PlayerDlg::OnCenterCut()
{
	isSideCut = false;
	isCenterCut = true;
	Player.CenterCut();
	PrintInfo();
}

void CMusic_PlayerDlg::PrintInfo() 
{
	CString strBass = (isBASS) ? L"��" : L"��";
	CString strReverse = (isReverse) ? L"��" : L"��";
	CString strSideCut = (isSideCut) ? L"��" : L"��";
	CString strCenterCut = (isCenterCut) ? L"��" : L"��";
	CString Info;
	Info.Format(L"״̬��\t\t\t\t%s\n������\t\t\t\t%d\nrate��\t\t\t\t%d\ntempo��\t\t\t%d\npitch��\t\t\t\t%d\n�Ƿ�BASS��\t\t\t%s\n�Ƿ�ת��\t\t\t%s\n�Ƿ��������ࣺ\t\t%s\n�Ƿ�����������\t\t%s\n", strStatus, volume, rate, tempo, pitch, strBass, strReverse, strSideCut, strCenterCut);
	m_info.SetWindowText(Info);
}

void CMusic_PlayerDlg::OnPitchChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	pitch = 0-m_Pitch_slider.GetPos();
	Player.SetPitch(pitch);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnTempoChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	tempo = 0-m_Tempo_slider.GetPos();
	Player.SetTempo(tempo);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnRateChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	rate = 0-m_Rate_slider.GetPos();
	Player.SetRate(rate);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::OnVolumeChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	volume = 0-m_Volume_slider.GetPos();
	Player.SetVolume(volume, volume);
	PrintInfo();
	*pResult = 0;
}

void CMusic_PlayerDlg::BASS() 
{
	if (!isBASS) 
	{
		Player.SetEQ(BassEffect);
		isBASS = !isBASS;
	}
	else 
	{
		Player.RestoreEQ(BassEffect);
		isBASS = !isBASS;
	}
	PrintInfo();
}

void CMusic_PlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	wchar_t szFilePathName[_MAX_PATH + 1] = { 0 };

	//�õ��ļ�����      
	UINT nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	//���õ��ļ���   
	DragQueryFile(hDropInfo, 0, szFilePathName, _MAX_PATH);
	Stop();
	CString path = szFilePathName;

	CT2CA pszConvertedAnsiString(path);
	string returnstring(pszConvertedAnsiString);


	Player.Open(returnstring.c_str());
	Play();

	DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}
