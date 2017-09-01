// AnimationShow.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CAnimationShowApp:
// 有关此类的实现，请参阅 AnimationShow.cpp
//

class CAnimationShowApp : public CWinApp
{
public:
	CAnimationShowApp();

// 重写
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	ULONG_PTR m_gdiplusToken;  
	
// 实现

	DECLARE_MESSAGE_MAP()
	BOOL RegisterClass(LPCTSTR lpszClassName);
	// 显示桌面
	void ShowDesktop(void);
};

extern CAnimationShowApp theApp;