#pragma once
#include "layeredwnd.h"

class CSnowWindow :
	public CLayeredWnd
{
public:
	CSnowWindow(void);
	virtual ~CSnowWindow(void);
private:
	CArray<LPAnimationImage,LPAnimationImage> m_SnowArray;//雪花图片数组
	int m_SnowCount;//雪花图片数量
	int m_RowCount;//每行图片数量
	int m_AllCount;//可显示图片总数
public:
	BOOL Create(HWND hWndParent=NULL);
	void InitImage();
	void AddAnimation(LPCTSTR lpName,int nAngle);
	void AddSnow(int nCount);
	void DownSnow();
	int GetRndNum(int nMin,int nMax);
	Gdiplus::Image* MakeAngleImage(LPAnimationImage pImage,int& nNewWidth,int& nNewHeight);//旋转图片
public:
	virtual void OnDrawWindow(Gdiplus::Graphics* pGraphics);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
