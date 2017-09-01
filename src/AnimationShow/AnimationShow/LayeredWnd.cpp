// LayeredWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AnimationShow.h"
#include "LayeredWnd.h"


// CLayeredWnd

IMPLEMENT_DYNAMIC(CLayeredWnd, CWnd)

CLayeredWnd::CLayeredWnd()
{
	m_nWidth=0;
	m_nHeight=0;
	m_ImageCount=0;
}

CLayeredWnd::~CLayeredWnd()
{
	ReleaseImage();
}


BEGIN_MESSAGE_MAP(CLayeredWnd, CWnd)
END_MESSAGE_MAP()

// ���ͼƬ������
LPAnimationImage CLayeredWnd::AddImage(LPCTSTR lpName,LPCTSTR lpType)
{
	LPAnimationImage pImage=new AnimationImage;
	ZeroMemory(pImage,sizeof(AnimationImage));
	LoadImage(pImage,lpName,lpType);
	m_ImageArray.Add(pImage);
	m_ImageCount=m_ImageArray.GetCount();
	return pImage;
}
// ����ͼƬ
BOOL CLayeredWnd::LoadImage(LPAnimationImage pImage,LPCTSTR lpName,LPCTSTR lpType)
{
	if(pImage->pImage)
	{
		delete pImage->pImage;
		pImage->pImage=NULL;
	}
	ZeroMemory(pImage,sizeof(AnimationImage));
	//------------------------------
	HINSTANCE hIns=::GetModuleHandle(NULL);
	HRSRC hRsrc = ::FindResource (hIns,lpName,lpType); // type 
	if (!hRsrc) 
		return FALSE; 
	// load resource into memory 
	DWORD len = SizeofResource(hIns, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hIns, hRsrc); 
	if (!lpRsrc) 
		return FALSE; 
	// Allocate global memory on which to create stream 
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len); 
	BYTE* pmem = (BYTE*)GlobalLock(hMem); 
	memcpy(pmem,lpRsrc,len); 
	IStream* pstm; 
	CreateStreamOnHGlobal(hMem,FALSE,&pstm); 
	// load from stream 
	pImage->pImage=Gdiplus::Image::FromStream(pstm); 
	//------------------------------
	if(!pImage->pImage)
		return FALSE;
	pImage->Width=pImage->pImage->GetWidth();
	pImage->Height=pImage->pImage->GetHeight();

	GlobalUnlock(hMem); 
	pstm->Release(); 
	FreeResource(lpRsrc);
	return TRUE;
}
// �ͷ�ͼƬ����
void CLayeredWnd::ReleaseImage()
{
	m_ImageCount=m_ImageArray.GetCount();
	for(int i=0;i<m_ImageCount;i++)
	{
		LPAnimationImage pImage=m_ImageArray.GetAt(i);
		//if(pImage->pImage)
		//{
		//	delete pImage->pImage;
		//	pImage->pImage=NULL;
		//}
		delete pImage;
	}
	m_ImageArray.RemoveAll();
	m_ImageCount=0;
}

// ���»��ƴ���
void CLayeredWnd::ReDrawWindow(void)
{
	HDC hDC=::GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = m_nHeight;
	bitmapinfo.bmiHeader.biWidth = m_nWidth;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject (hMemDC,hBitmap);
	Graphics g(hMemDC);
	//-------------------------------------------------------------
	OnDrawWindow(&g);
	//����͸������-------------------------------------------------
	CPoint DestPt(0,0);
	CSize psize(m_nWidth,m_nHeight);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	//�ͷ���Դ-------------------------------------------------
	::SelectObject (hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hWnd,hDC);
}
// �麯�� ���ƴ���
void CLayeredWnd::OnDrawWindow(Gdiplus::Graphics* pGraphics)
{

}
Gdiplus::Image* CLayeredWnd::LoadResImage(LPCTSTR lpName,LPCTSTR lpType)
{
	HINSTANCE hIns=::GetModuleHandle(NULL);
	HRSRC hRsrc = ::FindResource (hIns,lpName,lpType); // type 
	if (!hRsrc) 
		return NULL; 
	// load resource into memory 
	DWORD len = SizeofResource(hIns, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hIns, hRsrc); 
	if (!lpRsrc) 
		return NULL; 
	// Allocate global memory on which to create stream 
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len); 
	BYTE* pmem = (BYTE*)GlobalLock(hMem); 
	memcpy(pmem,lpRsrc,len); 
	IStream* pstm; 
	CreateStreamOnHGlobal(hMem,FALSE,&pstm); 
	// load from stream 
	Gdiplus::Image* pImage=Gdiplus::Image::FromStream(pstm); 
	// free/release stuff 
	GlobalUnlock(hMem); 
	pstm->Release(); 
	FreeResource(lpRsrc);
	return pImage;
}