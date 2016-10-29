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
	void InitPlayer();
	void InitCtl();
	void InitCtlValue();
	void PrintInfo();
	void ApplyEQSettings();
	void SetEQPos();
	void PlayListItem(int index);

	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CMusicPlayer Player;
public:
	static int __stdcall StopdPlayerCallback(void * instance, void * user_data, TCallbackMessage message, unsigned int param1, unsigned int param2);
	afx_msg void Play();
	afx_msg void Stop();
	afx_msg void OnReverse();
	afx_msg void OnSideCut();
	afx_msg void BASS();
	afx_msg void Reset();
	afx_msg void ResetEQ();
	afx_msg void OnCenterCut();
	afx_msg void OnFastForward();
	afx_msg void OnFastBackward();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEQ1Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ2Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ3Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ4Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ5Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ6Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ7Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEQ8Change(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPitchChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTempoChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRateChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVolumeChange(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnFileListDblClick(NMHDR *pNMHDR, LRESULT *pResult);

	bool bInitFinished = false;
	bool bSetEQPos = false;
	int SelectedItme = 0;

	CStatic m_info;
	int rate = 100;
	int tempo = 100;
	int pitch = 100;
	unsigned int volume = 100;
	CString strStatus = L"Paused";

	CSliderCtrl m_Pitch_slider;
	CSliderCtrl m_Tempo_slider;
	CSliderCtrl m_Rate_slider;
	CSliderCtrl m_Volume_slider;

	CButton m_Play;
	CButton m_Stop;
	CButton m_BASS;
	CButton m_FastForward;
	CButton m_FastBackward;
	int EQEffect[8] = { 0,0,0,0,0,0,0,0 };
	//int EQEffect[8] = { 6400,800,-3200,-6400,-3200,800,6400,6400 };

	CSliderCtrl m_EQ1_slider;
	CSliderCtrl m_EQ2_slider;
	CSliderCtrl m_EQ3_slider;
	CSliderCtrl m_EQ4_slider;
	CSliderCtrl m_EQ5_slider;
	CSliderCtrl m_EQ6_slider;
	CSliderCtrl m_EQ7_slider;
	CSliderCtrl m_EQ8_slider;
	CStatic m_EQ1_static;
	CStatic m_EQ2_static;
	CStatic m_EQ3_static;
	CStatic m_EQ4_static;
	CStatic m_EQ5_static;
	CStatic m_EQ6_static;
	CStatic m_EQ7_static;
	CStatic m_EQ8_static;

	CListCtrl m_FileList;
};

