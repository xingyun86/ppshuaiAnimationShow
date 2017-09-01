#pragma once
#include "Global.h"

// CLayeredWnd

class CLayeredWnd : public CWnd
{
	DECLARE_DYNAMIC(CLayeredWnd)
public:
	int m_nWidth;
	int m_nHeight;
	CArray<LPAnimationImage,LPAnimationImage> m_ImageArray;//ͼƬ����
	int m_ImageCount;//ͼƬ����
public:
	CLayeredWnd();
	virtual ~CLayeredWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ����ͼƬ
	BOOL LoadImage(LPAnimationImage pImage,LPCTSTR lpName,LPCTSTR lpType=_T("PNG"));
	// ���ͼƬ������
	LPAnimationImage AddImage(LPCTSTR lpName,LPCTSTR lpType=_T("PNG"));
	// �ͷ�ͼƬ����
	void ReleaseImage();
	// ���»��ƴ���
	void ReDrawWindow(void);
	// �麯�� ���ƴ���
	virtual void OnDrawWindow(Gdiplus::Graphics* pGraphics);
private:
	Gdiplus::Image* LoadResImage(LPCTSTR lpName,LPCTSTR lpType);
};


