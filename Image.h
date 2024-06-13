#pragma once
#include "Config.h"
class Image
{
public:
	enum ImageLoadType
	{
		Resource,		// ���α׷��� ���ԵǴ� ������
		File,			// ���� �ð��� �ܺο��� �ε��ϴ� ������
		Empty,			// �� ��Ʈ�� �̹��� ����
		End
	};

	// class�� struct�� �������� ����
	// ���������ڰ� public�̳� private�̳�
	typedef struct tagImageInfo
	{
		HDC hMemDc;		// �̹��� �����͸� �����ϴ� �ڵ�(�޸� ������)
		HBITMAP hBitmap;// �̹��� ������
		HBITMAP hOldBit;// ���� �̹��� ������
		int width;		// ���� ũ��
		int height;		// ���� ũ��
		BYTE loadType;	// �ε� Ÿ��

		// �ִϸ��̼� �� ������
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			hMemDc = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = ImageLoadType::Empty;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		};
	} IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	HRESULT Init(int width, int height);	// �� ��Ʈ�� �̹��� ����(Empty)
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL); // File �������� ���� �̹���
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL); // File �������� �ִ� �̹���

	void Release();	// �޸� ����

	void Render(HDC hdc, int destX = 0, int destY = 0);
	void Render(HDC hdc, int destX, int destY, int frameX, int frameY, int width = 0, int height = 0, float scale = 1.0f);	// �̹��� �����͸� ȭ�鿡 ����
	void Render(HDC hdc, long destX, long destY, int frameX, int frameY, int width = 0, int height = 0, float scale = 1.0f);	// �̹��� �����͸� ȭ�鿡 ����
	void Render(HDC hdc, float destX, float destY, int frameX, int frameY, int width = 0, int height = 0, float scale = 1.0f);	// �̹��� �����͸� ȭ�鿡 ����

	HDC GetMemDC() { if (imageInfo) return imageInfo->hMemDc; return NULL; }
	LPIMAGE_INFO GetImageInfo() { return imageInfo; }

	int GetMaxFrameX() { return (int)imageInfo->maxFrameX; }
	int GetMaxFrameY() { return (int)imageInfo->maxFrameY; }

	int GetFrameWidth() { return (int)imageInfo->frameWidth; }
	int GetFrameHeight() { return (int)imageInfo->frameHeight; }

	int GetWidth() { return (int)imageInfo->width; }
	int GetHeight() { return (int)imageInfo->height; }
};

