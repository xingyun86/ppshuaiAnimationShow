#pragma once

#include <gdiplus.h>
using namespace Gdiplus; 
#pragma comment(lib,"GdiPlus.lib")

#define APP_CLASSNAME	_T("CometAnimationUI")		//窗口类名
#define APP_SOFTNAME	_T("雪花动画")				//软件名称

typedef struct tagAnimationImage
{
	Gdiplus::Image* pImage;
	int X;
	int Y;
	int Width;
	int Height;
	int Time;
	int Angle;//旋转角度
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