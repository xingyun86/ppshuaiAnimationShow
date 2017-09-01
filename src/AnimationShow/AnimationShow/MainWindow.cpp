#include "StdAfx.h"
#include "MainWindow.h"

CMainWindow::CMainWindow(void)
{
	m_pBkImage=new AnimationImage;
	ZeroMemory(m_pBkImage,sizeof(AnimationImage));
	m_nFrameIndex=0;
	m_nFrameTime=0;
	m_nTimer=0;
	m_bShowBk=FALSE;
	m_bTracking=FALSE;
}

CMainWindow::~CMainWindow(void)
{

}
BOOL CMainWindow::Create(HWND hWndParent)
{
	CRect rcWork;
	SystemParametersInfo (SPI_GETWORKAREA, NULL, rcWork, NULL);
	m_nWidth = 400;
	m_nHeight = 240;
	int x = rcWork.right - m_nWidth;
	int y = rcWork.bottom - m_nHeight;
	DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED;
	DWORD dwStyle = WS_POPUP | WS_VISIBLE | WS_SYSMENU;

	if(!CWnd::CreateEx(dwExStyle,APP_CLASSNAME,APP_SOFTNAME,dwStyle,x,y,m_nWidth,m_nHeight,hWndParent,NULL))
	{
		return FALSE;
	}
	//------------------------
	m_ToolTip.Create(this,TTS_ALWAYSTIP);
	EnableToolTips(TRUE);
	//------------------------
	InitImage();
	//------------------------
	x=339;
	y=6;
	int w=16;
	int h=16;
	AddControl(x,y,w,h,_T("XXX"));
	x+=20;
	AddControl(x,y,w,h,_T("XXX"));
	x+=20;
	AddControl(x,y,w,h,_T("退出本程序"));
	//------------------------
	SetFrame(0);
	SetTimer(1,10,NULL);
	return TRUE;
}
void CMainWindow::InitImage()
{
	LoadImage(m_pBkImage,_T("back.png"));
	AddAnimation(_T("Rabbit01.png"),50);
	AddAnimation(_T("Rabbit02.png"),7);
	AddAnimation(_T("Rabbit03.png"),7);
	AddAnimation(_T("Rabbit04.png"),7);
	AddAnimation(_T("Rabbit05.png"),7);
	AddAnimation(_T("Rabbit06.png"),50);
	AddAnimation(_T("Rabbit07.png"),10);
	AddAnimation(_T("Rabbit08.png"),15);
	AddAnimation(_T("Rabbit09.png"),10);
	AddAnimation(_T("Rabbit10.png"),15);
	AddAnimation(_T("Rabbit05.png"),7);
	AddAnimation(_T("Rabbit04.png"),7);
	AddAnimation(_T("Rabbit03.png"),7);
	AddAnimation(_T("Rabbit02.png"),7);
}
void CMainWindow::AddAnimation(LPCTSTR lpName,int nTime)
{
	LPAnimationImage pImage=AddImage(lpName);
	pImage->Time=nTime;
}
void CMainWindow::SetFrame(int nIndex)
{
	if(nIndex<0 || nIndex>=m_ImageCount)
		nIndex=0;
	m_nFrameIndex=nIndex;
	m_nFrameTime=m_ImageArray[m_nFrameIndex]->Time;
	m_nTimer=0;
	ReDrawWindow();
}
// 虚函数 绘制窗口
void CMainWindow::OnDrawWindow(Gdiplus::Graphics* pGraphics)
{
	if(m_bShowBk)
	{
		pGraphics->DrawImage(m_pBkImage->pImage,0,0,m_pBkImage->Width,m_pBkImage->Height);
	}

	LPAnimationImage pImage=m_ImageArray[m_nFrameIndex];
	pGraphics->DrawImage(pImage->pImage,0,m_nHeight-pImage->Height,pImage->Width,pImage->Height);
}
void CMainWindow::AddControl(int x, int y, int nWidth, int nHeight,LPCTSTR lpszTooltip)
{
	LPDUIControl pControl=new DUIControl;
	pControl->X=x;
	pControl->Y=y;
	pControl->Width=nWidth;
	pControl->Height=nHeight;
	pControl->Rect=CRect(x,y,x+nWidth,y+nHeight);
	m_ControlAyyay.Add(pControl);
	m_nControlCount=m_ControlAyyay.GetCount();
	if(lpszTooltip)
	{
		m_ToolTip.AddTool(this,lpszTooltip,&pControl->Rect,100+m_nControlCount);
	}
}
int CMainWindow::HitControl(CPoint point)
{
	int nIndex=-1;
	for (int i=0;i<m_nControlCount;i++)
	{
		LPDUIControl pControl=m_ControlAyyay.GetAt(i);
		if(::PtInRect(&pControl->Rect,point))
		{
			nIndex=i;
			break;
		}
	}
	return nIndex;
}
BEGIN_MESSAGE_MAP(CMainWindow, CLayeredWnd)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

void CMainWindow::OnTimer(UINT_PTR nIDEvent)
{
	CLayeredWnd::OnTimer(nIDEvent);
	m_nTimer++;
	if(m_nTimer>=m_nFrameTime)
	{
		SetFrame(m_nFrameIndex+1);
	}
}

void CMainWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	if   (!m_bTracking) 
	{ 
		TRACKMOUSEEVENT   tme; 
		tme.cbSize   =   sizeof(tme); 
		tme.hwndTrack   =   m_hWnd; 
		tme.dwFlags   =   TME_LEAVE|TME_HOVER; 
		tme.dwHoverTime   =   10; 
		m_bTracking   =   _TrackMouseEvent(&tme); 
	} 	

	CLayeredWnd::OnMouseMove(nFlags, point);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	CLayeredWnd::OnLButtonDown(nFlags, point);
	if(HitControl(point)==-1)
	{
		ReleaseCapture();
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION);
	}
}

void CMainWindow::OnLButtonUp(UINT nFlags, CPoint point)
{
	CLayeredWnd::OnLButtonUp(nFlags, point);
	int nIndex=HitControl(point);
	switch (nIndex)
	{
	case 0:
		ShellExecute(NULL,_T("Open"),_T("about:blank"),NULL,NULL,SW_SHOW);
		break;
	case 1:
		ShellExecute(NULL,_T("Open"),_T("about:blank"),NULL,NULL,SW_SHOW);
		break;
	case 2:
		PostMessage(WM_CLOSE);
		break;
	}
}
LRESULT CMainWindow::OnMouseHover(WPARAM wParam,LPARAM lParam)
{
	//m_bShowBk=TRUE;
	ReDrawWindow();
	return 0;
}
LRESULT CMainWindow::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	m_bShowBk=FALSE;
	m_bTracking=FALSE;
	ReDrawWindow();
	return 0;
}
BOOL CMainWindow::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	return CLayeredWnd::PreTranslateMessage(pMsg);
}
