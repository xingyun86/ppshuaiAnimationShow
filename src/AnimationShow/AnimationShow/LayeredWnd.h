#pragma once
#include "Global.h"

// CLayeredWnd

class CLayeredWnd : public CWnd
{
	DECLARE_DYNAMIC(CLayeredWnd)
public:
	int m_nWidth;
	int m_nHeight;
	CArray<LPAnimationImage,LPAnimationImage> m_ImageArray;//图片数组
	int m_ImageCount;//图片数量
public:
	CLayeredWnd();
	virtual ~CLayeredWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// 载入图片
	BOOL LoadImage(LPAnimationImage pImage,LPCTSTR lpName,LPCTSTR lpType=_T("PNG"));
	// 添加图片到数组
	LPAnimationImage AddImage(LPCTSTR lpName,LPCTSTR lpType=_T("PNG"));
	// 释放图片数组
	void ReleaseImage();
	// 重新绘制窗口
	void ReDrawWindow(void);
	// 虚函数 绘制窗口
	virtual void OnDrawWindow(Gdiplus::Graphics* pGraphics);
private:
	Gdiplus::Image* LoadResImage(LPCTSTR lpName,LPCTSTR lpType);
};


