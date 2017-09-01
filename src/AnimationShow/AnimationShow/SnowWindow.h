#pragma once
#include "layeredwnd.h"

class CSnowWindow :
	public CLayeredWnd
{
public:
	CSnowWindow(void);
	virtual ~CSnowWindow(void);
private:
	CArray<LPAnimationImage,LPAnimationImage> m_SnowArray;//ѩ��ͼƬ����
	int m_SnowCount;//ѩ��ͼƬ����
	int m_RowCount;//ÿ��ͼƬ����
	int m_AllCount;//����ʾͼƬ����
public:
	BOOL Create(HWND hWndParent=NULL);
	void InitImage();
	void AddAnimation(LPCTSTR lpName,int nAngle);
	void AddSnow(int nCount);
	void DownSnow();
	int GetRndNum(int nMin,int nMax);
	Gdiplus::Image* MakeAngleImage(LPAnimationImage pImage,int& nNewWidth,int& nNewHeight);//��תͼƬ
public:
	virtual void OnDrawWindow(Gdiplus::Graphics* pGraphics);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
