
// Music_Player.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMusic_PlayerApp: 
// �йش����ʵ�֣������ Music_Player.cpp
//

class CMusic_PlayerApp : public CWinApp
{
public:
	CMusic_PlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMusic_PlayerApp theApp;