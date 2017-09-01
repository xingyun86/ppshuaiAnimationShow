// AnimationShow.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "AnimationShow.h"
#include "MainWindow.h"
#include "SnowWindow.h"

#include <shldisp.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimationShowApp

BEGIN_MESSAGE_MAP(CAnimationShowApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAnimationShowApp 构造

CAnimationShowApp::CAnimationShowApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CAnimationShowApp 对象

CAnimationShowApp theApp;


// CAnimationShowApp 初始化

BOOL CAnimationShowApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	if (!RegisterClass(APP_CLASSNAME))
	{
		return FALSE;
	}
//	ShowDesktop();

	CMainWindow mainWnd;
	CSnowWindow snowWnd;
	if (!mainWnd.Create())
	{
		return FALSE;
	}
	snowWnd.Create(mainWnd.m_hWnd);
	m_pMainWnd = &mainWnd;
	Run();
	return FALSE;
}
int CAnimationShowApp::ExitInstance()
{
	// 卸载GDI+
	GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}
BOOL CAnimationShowApp::RegisterClass(LPCTSTR lpszClassName)
{
	WNDCLASS wndcls;
	memset(&wndcls,0,sizeof(WNDCLASS));
	wndcls.style=CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;
	wndcls.lpfnWndProc=::DefWindowProc;
	wndcls.hInstance=AfxGetInstanceHandle();
	wndcls.hIcon=NULL;
	wndcls.hCursor=::LoadCursor(NULL,IDC_ARROW);
	wndcls.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	wndcls.lpszMenuName=NULL;
	wndcls.lpszClassName=lpszClassName;
	if(!AfxRegisterClass(&wndcls))
	{
		TRACE("Class　Registration　Failedn");
		return FALSE;
	}
	return TRUE;
}

// 显示桌面
void CAnimationShowApp::ShowDesktop(void)
{
	CoInitialize(0);
	IShellDispatch4 *pdisp = NULL;
	CoCreateInstance(CLSID_Shell, NULL, CLSCTX_ALL, __uuidof(IShellDispatch4),(void**)&pdisp);
	pdisp-> ToggleDesktop(); // 这句是用来切换桌面的
	pdisp-> Release();

}
