#pragma once
#include "Image.h"
#include <Windows.h>
#include <math.h>
#include "Config.h"
#include <array>
inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 원하는 윈도우 작업영역 설정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// 스타일이 포함된 실제 윈도우 크기 계산
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 계산된 값으로 윈도우를 이동시키면서 크기도 함께 변환
	MoveWindow(g_hWnd, startX, startY,
		rc.right - rc.left, rc.bottom - rc.top, true);
}

inline POINT GetPosTile(POINTFLOAT pos) {
	int CountX = 0;
	CountX = ((int)pos.x / TILE_SIZE);
	if (CountX < 0) CountX = 0;

	int CountY = 0;
	CountY = ((int)pos.y / TILE_SIZE);
	if (CountY < 0) CountY = 0;
	
	POINT result{ CountX ,CountY };
	return result;
}

inline void SetRect(RECT* rect, POINTFLOAT pos,int bodySize)
{
	rect->left = (LONG)pos.x - (bodySize / 2);
	rect->right = (LONG)pos.x + (bodySize / 2);
	rect->top = (LONG)pos.y - (bodySize / 2);
	rect->bottom = (LONG)pos.y + (bodySize / 2);
}

inline void SetRect(RECT* rect, POINTFLOAT pos, int bodySizeX, int bodySizeY)
{
	rect->left = (LONG)pos.x - (bodySizeX / 2);
	rect->right = (LONG)pos.x + (bodySizeX / 2);
	rect->top = (LONG)pos.y - (bodySizeY / 2);
	rect->bottom = (LONG)pos.y + (bodySizeY / 2);
}

inline POINT GetMousePoint()
{
	RECT rect;
	POINT mouse = Input::GetMousePosition();
	POINT view;
	GetClientRect(g_hWnd, &rect);
	view.x = rect.right - rect.left;
	view.y = rect.bottom - rect.top;
	if (view.x != WIN_SIZE_X || view.y != WIN_SIZE_Y)
	{
		view.x /= WIN_SIZE_X;
		view.y /= WIN_SIZE_Y;
		mouse.x /= view.x;
		mouse.y /= view.y;
	}
	return mouse;
}

inline void PrintText(HDC hdc, char* text, int posX, int posY, int size = 8)
{
	HFONT font , oldfont;
	SetBkMode(hdc, 1);
	SetTextColor(hdc, RGB(255, 255, 255));
	font = CreateFont(
		size,			// 폰트의 높이
		0,			// 폰트의 폭
		0,			// 폰트의 각도
		0,			// 각 글자의 각도
		1,			// 폰트의 두꺠
		0,			// 기울임체
		0,			// 밑줄
		0,			// 관통성
		0,			// 문자셋
		0,			// 출력정확도
		0,			// 클리핑 정확도
		0,			// 논리적 폰트(?)
		0,			// 폰트의 피치와 그룹
		"돋음");		// 글꼴
	oldfont = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, posX-1, posY, text, lstrlen(text)); // 텍스트 테두리 출력 
	TextOut(hdc, posX+1, posY, text, lstrlen(text)); // 텍스트 테두리 출력 
	TextOut(hdc, posX, posY-1, text, lstrlen(text)); // 텍스트 테두리 출력 
	TextOut(hdc, posX, posY+1, text, lstrlen(text)); // 텍스트 테두리 출력 

	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, posX, posY, text, lstrlen(text)); // 텍스트 출력 
	SelectObject(hdc, oldfont);
	DeleteObject(font);
}
