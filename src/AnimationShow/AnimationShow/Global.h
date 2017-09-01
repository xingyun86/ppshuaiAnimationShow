#pragma once

#include <gdiplus.h>
using namespace Gdiplus; 
#pragma comment(lib,"GdiPlus.lib")

#define APP_CLASSNAME	_T("CometAnimationUI")		//��������
#define APP_SOFTNAME	_T("ѩ������")				//�������

typedef struct tagAnimationImage
{
	Gdiplus::Image* pImage;
	int X;
	int Y;
	int Width;
	int Height;
	int Time;
	int Angle;//��ת�Ƕ�
	int OffsetPos;
	int OffsetMax;
	int OffsetMode;
} AnimationImage, *PAnimationImage,FAR *LPAnimationImage;

typedef struct tagDUIControl
{
	int X;
	int Y;
	int Width;
	int Height;
	RECT Rect;
} DUIControl, *PDUIControl,FAR *LPDUIControl;