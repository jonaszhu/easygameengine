// Mole2dGameClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMole2dGameClientApp:
// �йش����ʵ�֣������ Mole2dGameClient.cpp
//

class CMole2dGameClientApp : public CWinApp
{
public:
	CMole2dGameClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMole2dGameClientApp theApp;
