// AnimationShow.cpp : ����Ӧ�ó��������Ϊ��
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


// CAnimationShowApp ����

CAnimationShowApp::CAnimationShowApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAnimationShowApp ����

CAnimationShowApp theApp;


// CAnimationShowApp ��ʼ��

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
	// ж��GDI+
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
		TRACE("Class��Registration��Failedn");
		return FALSE;
	}
	return TRUE;
}

// ��ʾ����
void CAnimationShowApp::ShowDesktop(void)
{
	CoInitialize(0);
	IShellDispatch4 *pdisp = NULL;
	CoCreateInstance(CLSID_Shell, NULL, CLSCTX_ALL, __uuidof(IShellDispatch4),(void**)&pdisp);
	pdisp-> ToggleDesktop(); // ����������л������
	pdisp-> Release();

}
