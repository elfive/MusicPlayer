#pragma once
#include "MusicPlayer.h"
#include "afxwin.h"
#include "afxcmn.h"

class CMusic_PlayerDlg : public CDialogEx
{
// 构造
public:
	CMusic_PlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSIC_PLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	void InitCtl();	
	void PrintInfo();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CMusicPlayer Player;
public:
	afx_msg void Play();
	afx_msg void Stop();
	afx_msg void OnReverse();
	afx_msg void OnSideCut();
	afx_msg void BASS();
	afx_msg void OnCenterCut();
	afx_msg void OnPitchChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTempoChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRateChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVolumeChange(NMHDR * pNMHDR, LRESULT * pResult);

	CStatic m_info;
	int rate = 100;
	int tempo = 100;
	int pitch = 100;
	unsigned int volume = 100;
	bool isReverse = false;
	bool isSideCut = false;
	bool isCenterCut = false;
	bool isBASS = false;
	CString strStatus = L"暂未播放";

	CSliderCtrl m_Pitch_slider;
	CSliderCtrl m_Tempo_slider;
	CSliderCtrl m_Rate_slider;
	CSliderCtrl m_Volume_slider;

	CButton m_Play;
	CButton m_Stop;
	CButton m_BASS;

	//int BassEffect[8] = { -3200,-1600,-800,0,2000,3000,4000,5000 };
	int BassEffect[8] = { 6400,800,-3200,-6400,-3200,800,6400,6400 };
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
