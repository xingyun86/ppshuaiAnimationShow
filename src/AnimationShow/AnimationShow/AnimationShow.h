// AnimationShow.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAnimationShowApp:
// �йش����ʵ�֣������ AnimationShow.cpp
//

class CAnimationShowApp : public CWinApp
{
public:
	CAnimationShowApp();

// ��д
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	ULONG_PTR m_gdiplusToken;  
	
// ʵ��

	DECLARE_MESSAGE_MAP()
	BOOL RegisterClass(LPCTSTR lpszClassName);
	// ��ʾ����
	void ShowDesktop(void);
};

extern CAnimationShowApp theApp;