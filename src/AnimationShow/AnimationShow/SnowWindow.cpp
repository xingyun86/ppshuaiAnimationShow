#include "StdAfx.h"
#include "SnowWindow.h"
#include <math.h> 

CSnowWindow::CSnowWindow(void)
{

}

CSnowWindow::~CSnowWindow(void)
{

}
BOOL CSnowWindow::Create(HWND hWndParent)
{
	m_nWidth = GetSystemMetrics (SM_CXSCREEN);
	m_nHeight =  GetSystemMetrics (SM_CYSCREEN);
	int x = 0;
	int y = 0;
	DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT;
	DWORD dwStyle = WS_POPUP | WS_VISIBLE | WS_SYSMENU;

	if(!CWnd::CreateEx(dwExStyle,APP_CLASSNAME,APP_SOFTNAME,dwStyle,x,y,m_nWidth,m_nHeight,hWndParent,NULL))
		return FALSE;

	srand( (unsigned)time( NULL ) );
	InitImage();
	SetTimer(1,100,NULL);
	return TRUE;
}
void CSnowWindow::InitImage()
{
	AddAnimation(_T("Snow01.png"),0);
	AddAnimation(_T("Snow02.png"),0);
	AddAnimation(_T("Snow03.png"),-1);
	AddAnimation(_T("Snow04.png"),-1);
	AddAnimation(_T("Snow05.png"),0);
	AddAnimation(_T("Snow06.png"),0);
	AddAnimation(_T("Snow07.png"),0);
	AddAnimation(_T("Snow08.png"),0);
	AddAnimation(_T("Snow09.png"),0);
	AddAnimation(_T("Snow10.png"),0);
	AddAnimation(_T("Snow11.png"),0);
	AddAnimation(_T("Snow12.png"),0);


	m_RowCount=m_nWidth/(m_ImageArray[0]->Width+20);
	m_AllCount=m_RowCount*(m_nHeight/(m_ImageArray[0]->Height+20));
	AddSnow(m_RowCount);
}
void CSnowWindow::AddAnimation(LPCTSTR lpName,int nAngle)
{
	LPAnimationImage pImage=AddImage(lpName);
	pImage->Angle=nAngle;
}
//���ѩ��ͼƬ
void CSnowWindow::AddSnow(int nCount)
{
	for(int i=0;i<nCount;i++)
	{
		//���ȡһ��ͼƬ
		int nIndex=GetRndNum(0,m_ImageCount-1);
		LPAnimationImage pImage=new AnimationImage;
		LPAnimationImage pSrcImage=m_ImageArray[nIndex];
		CopyMemory(pImage,pSrcImage,sizeof(AnimationImage));

		//�������ͼƬ�ĳ�ʼλ��
		pImage->X=GetRndNum(0,m_nWidth);
		pImage->Y=0-GetRndNum(pImage->Height,pImage->Height*2);

		//�������ͼƬ
		float f=(float)GetRndNum(50,100);
		f=f/(float)100;
		pImage->Width=(int)((float)pImage->Width*f);
		pImage->Height=(int)((float)pImage->Height*f);

		//������ó�ʼ�Ƕ�
		if(pImage->Angle>=0)
			pImage->Angle=GetRndNum(0,360);

		m_SnowArray.Add(pImage);

	}
	m_SnowCount=m_SnowArray.GetCount();
}
//����ѩ��ͼƬ
void CSnowWindow::DownSnow()
{
	int nTop=25;
	for(int i=m_SnowCount-1;i>=0;i--)
	{
		LPAnimationImage pImage=m_SnowArray[i];
		pImage->Y+=5;//����
		if(pImage->Y>m_nHeight)//������Ļ�߶�
		{
			m_SnowArray.RemoveAt(i);//�Ƴ�����ͼƬ
			delete pImage;
			continue;//ת����һ��ѭ��
		}
		//-------------
		if(pImage->Y<nTop)
			nTop=pImage->Y;
		//-------------
		//��תͼƬ
		if(pImage->Angle>=0)
		{
			pImage->Angle+=10;
			if(pImage->Angle>=360)
				pImage->Angle=0;
		}
		//-------------
		//�����ƶ� 
		if(pImage->OffsetPos==0 || pImage->OffsetPos>pImage->OffsetMax)
		{
			pImage->OffsetPos=0;
			pImage->OffsetMax=GetRndNum(30,120);
			pImage->OffsetMode=GetRndNum(1,3);
		}
		pImage->OffsetPos++;
		switch (pImage->OffsetMode)
		{
		case 1:
			pImage->X--;
			break;
		case 2:
			pImage->X++;
			break;
		}
	}
	m_SnowCount=m_SnowArray.GetCount();
	int nCount=m_AllCount-m_SnowCount;
	if(nCount>0 && nTop>20)
	{
		if(nCount>m_RowCount)
			nCount=m_RowCount;
		AddSnow(nCount);
	}
	ReDrawWindow();
}
int CSnowWindow::GetRndNum(int nMin,int nMax)
{
	int r=nMin + rand() % (nMax-nMin+1);
	return r;
}
// �麯�� ���ƴ���
void CSnowWindow::OnDrawWindow(Gdiplus::Graphics* pGraphics)
{
	for(int i=0;i<m_SnowCount;i++)
	{
		LPAnimationImage pImage=m_SnowArray[i];
		if(pImage->Angle>0)
		{
			int nNewWidth=0;
			int nNewHeight=0;
			Gdiplus::Image* pNewImage=MakeAngleImage(pImage,nNewWidth,nNewHeight);
			pGraphics->DrawImage(pNewImage,pImage->X,pImage->Y,nNewWidth,nNewHeight);
			delete pNewImage;
		}else{
			
			pGraphics->DrawImage(pImage->pImage,pImage->X,pImage->Y,pImage->Width,pImage->Height);
		}
		
	}
}
//��תͼƬ
Gdiplus::Image* CSnowWindow::MakeAngleImage(LPAnimationImage pImage,int& nNewWidth,int& nNewHeight)
{
	double Width=(double)pImage->Width;//ԭͼ�ߴ�
	double Height=(double)pImage->Height;//ԭͼ�ߴ�
	double fAngle=(double)pImage->Angle;//��ת�Ƕ�
	double pi=3.1415926535f;
	double AngleSin=sin(double(fAngle*pi/180.0f));
	double AngleCos=cos(fAngle*pi/180.0f);
	nNewWidth=(INT)(abs(Height*AngleSin)+abs(Width*AngleCos));//����ת����ͼ��Ŀ��
	nNewHeight=(INT)(abs(Height*AngleCos)+abs(Width*AngleSin));//����ת����ͼ��ĸ߶�
	Gdiplus::Image* pNewImage=new Gdiplus::Bitmap(nNewWidth,nNewHeight,PixelFormat32bppARGB);

	Matrix matrix;
	//matrix.Translate(((float)nNewWidth - Width) / 2.0f, ((float)nNewHeight - Height) / 2.0f,MatrixOrderPrepend); // ƫ�����꣬ʹ�¾�ͼ���������������ص�
	//matrix.Translate( Width / 2.0f, Height / 2.0f,MatrixOrderPrepend); // ƫ�����꣬ʹ��ͼ�����Ͻǵĵ�����ͼ������
	//matrix.Rotate(fAngle,MatrixOrderPrepend); // ��ת����
	//matrix.Translate( -(Width / 2.0f), -(Height / 2.0f),MatrixOrderPrepend); // ƫ�����꣬ʹ�¾�ͼ�������������������ص�
	PointF ptCenter(Width / 2.0f, Height / 2.0f);
	matrix.RotateAt(fAngle,ptCenter,MatrixOrderPrepend);

	Gdiplus::Graphics g(pNewImage);
	g.SetTransform(&matrix); // Ӧ���趨����

	g.DrawImage(pImage->pImage,0,0,pImage->Width,pImage->Height);

	//g.ResetTransform();    //������ϵ��λ

	return pNewImage;
}
BEGIN_MESSAGE_MAP(CSnowWindow, CLayeredWnd)
ON_WM_TIMER()
END_MESSAGE_MAP()

void CSnowWindow::OnTimer(UINT_PTR nIDEvent)
{
	CLayeredWnd::OnTimer(nIDEvent);
	DownSnow();
}
