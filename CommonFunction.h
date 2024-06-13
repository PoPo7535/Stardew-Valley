#pragma once
#include "Image.h"
#include <Windows.h>
#include <math.h>
#include "Config.h"
#include <array>
inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// ���ϴ� ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = sizeX;	rc.bottom = sizeY;

	// ��Ÿ���� ���Ե� ���� ������ ũ�� ���
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// ���� ������ �����츦 �̵���Ű�鼭 ũ�⵵ �Բ� ��ȯ
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
		size,			// ��Ʈ�� ����
		0,			// ��Ʈ�� ��
		0,			// ��Ʈ�� ����
		0,			// �� ������ ����
		1,			// ��Ʈ�� �΃�
		0,			// �����ü
		0,			// ����
		0,			// ���뼺
		0,			// ���ڼ�
		0,			// �����Ȯ��
		0,			// Ŭ���� ��Ȯ��
		0,			// ���� ��Ʈ(?)
		0,			// ��Ʈ�� ��ġ�� �׷�
		"����");		// �۲�
	oldfont = (HFONT)SelectObject(hdc, font);
	TextOut(hdc, posX-1, posY, text, lstrlen(text)); // �ؽ�Ʈ �׵θ� ��� 
	TextOut(hdc, posX+1, posY, text, lstrlen(text)); // �ؽ�Ʈ �׵θ� ��� 
	TextOut(hdc, posX, posY-1, text, lstrlen(text)); // �ؽ�Ʈ �׵θ� ��� 
	TextOut(hdc, posX, posY+1, text, lstrlen(text)); // �ؽ�Ʈ �׵θ� ��� 

	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, posX, posY, text, lstrlen(text)); // �ؽ�Ʈ ��� 
	SelectObject(hdc, oldfont);
	DeleteObject(font);
}
