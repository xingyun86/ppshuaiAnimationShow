#pragma once
#include "layeredwnd.h"

class CMainWindow :
	public CLayeredWnd
{
public:
	CMainWindow(void);
	virtual ~CMainWindow(void);
private:
	BOOL m_bShowBk;
	LPAnimationImage m_pBkImage;
	int m_nFrameIndex;
	int m_nFrameTime;
	int m_nTimer;
	BOOL m_bTracking;
	CArray<LPDUIControl,LPDUIControl> m_ControlAyyay;
	int m_nControlCount;
	CToolTipCtrl m_ToolTip;
public:
	BOOL Create(HWND hWndParent=NULL);
	void InitImage();
	void SetFrame(int nIndex);
	void AddAnimation(LPCTSTR lpName,int nTime);
	int HitControl(CPoint point);
	void AddControl(int x, int y, int nWidth, int nHeight,LPCTSTR lpszTooltip);
public:
	virtual void OnDrawWindow(Gdiplus::Graphics* pGraphics);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHover(WPARAM wParam,LPARAM lParam) ;
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam) ;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
