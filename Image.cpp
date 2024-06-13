#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);		// 권한이 굉장히 많은 총지배인

	// 빈 비트맵 생성
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 
											// 기본적으로 Bitmap에 연결되어 있다.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// 비트맵 생성에 실패했을 때
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height,
	bool isTrans/* = false*/, COLORREF transColor/* = NULL*/)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 
											// 기본적으로 Bitmap에 연결되어 있다.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,
	bool isTrans, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::File;
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,
		LR_LOADFROMFILE);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// 새로 생성된 DC 
											// 기본적으로 Bitmap에 연결되어 있다.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	this->isTransparent = isTrans;
	this->transColor = transColor;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->currFrameX = 0;
	imageInfo->currFrameY = 0;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}

void Image::Release()
{
	if (imageInfo)
	{
		SelectObject(imageInfo->hMemDc, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDc);

		delete imageInfo;
		imageInfo = nullptr;
	}
}

void Image::Render(HDC hdc, int destX, int destY)
{
	BitBlt(hdc,				// 복사 목적지 DC
		destX,					// 복사될 비트맵의 시작 위치 x
		destY,					// 복사될 비트맵의 시작 위치 y
		imageInfo->width,	// 원본 복사할 가로 크기
		imageInfo->height,	// 원본 복사할 세로 크기
		imageInfo->hMemDc,	// 원본 DC
		0,					// 원본 비트맵 복사 시작 위치 x
		0,					// 원본 비트맵 복사 시작 위치 y
		SRCCOPY);			// 복사 옵션
}

void Image::Render(HDC hdc, int destX, int destY, int frameX, int frameY, int width, int height, float scale/* = 1.0f*/)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			(int)(destX -(imageInfo->frameWidth / 2)),
			(int)(destY -(imageInfo->frameHeight / 2)),
			(int)(imageInfo->frameWidth * scale),
			(int)(imageInfo->frameHeight * scale),	// 전체 프레임 수

			imageInfo->hMemDc,
			(int)(imageInfo->frameWidth* frameX),
			(int)(imageInfo->frameHeight* frameY),
			(int)(imageInfo->frameWidth* (width + 1)),
			(int)(imageInfo->frameHeight * (height + 1)),
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// 복사 목적지 DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// 복사될 비트맵의 시작 위치 x
			(int)(destY - (imageInfo->frameHeight / 2)),		// 복사될 비트맵의 시작 위치 y
			(int)(imageInfo->frameWidth * scale),	// 원본 복사할 가로 크기
			(int)(imageInfo->frameHeight * scale),	// 원본 복사할 세로 크기
			imageInfo->hMemDc,	// 원본 DC
			(int)(imageInfo->frameWidth * frameX),				// 원본 비트맵 복사 시작 위치 x
			(int)(imageInfo->frameHeight * frameY),			// 원본 비트맵 복사 시작 위치 y
			SRCCOPY);			// 복사 옵션
	}
}

void Image::Render(HDC hdc, long destX, long destY, int frameX, int frameY, int width, int height, float scale/* = 1.0f*/)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			(int)(destX - (imageInfo->frameWidth / 2)),
			(int)(destY - (imageInfo->frameHeight / 2)),
			(int)(imageInfo->frameWidth * scale),
			(int)(imageInfo->frameHeight * scale),	// 전체 프레임 수

			imageInfo->hMemDc,
			(int)(imageInfo->frameWidth * frameX),
			(int)(imageInfo->frameHeight * frameY),
			(int)(imageInfo->frameWidth * (width + 1)),
			(int)(imageInfo->frameHeight * (height + 1)),
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// 복사 목적지 DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// 복사될 비트맵의 시작 위치 x
			(int)(destY - (imageInfo->frameHeight / 2)),		// 복사될 비트맵의 시작 위치 y
			(int)(imageInfo->frameWidth * scale),	// 원본 복사할 가로 크기
			(int)(imageInfo->frameHeight * scale),	// 원본 복사할 세로 크기
			imageInfo->hMemDc, 	// 원본 DC
			(int)(imageInfo->frameWidth * frameX), 				// 원본 비트맵 복사 시작 위치 x
			(int)(imageInfo->frameHeight * frameY), 			// 원본 비트맵 복사 시작 위치 y
			SRCCOPY);			// 복사 옵션
	}
}

void Image::Render(HDC hdc, float destX, float destY, int frameX, int frameY, int width, int height, float scale/* = 1.0f*/)
{
	if (isTransparent)
	{
		GdiTransparentBlt(
			hdc,
			(int)(destX - (imageInfo->frameWidth / 2)),
			(int)(destY - (imageInfo->frameHeight / 2)),
			(int)(imageInfo->frameWidth * scale),
			(int)(imageInfo->frameHeight * scale),	// 전체 프레임 수

			imageInfo->hMemDc,
			(int)(imageInfo->frameWidth * frameX), 
			(int)(imageInfo->frameHeight * frameY),
			(int)(imageInfo->frameWidth* (width + 1)),
			(int)(imageInfo->frameHeight * (height + 1)),
			transColor
		);
	}
	else
	{
		BitBlt(hdc,				// 복사 목적지 DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// 복사될 비트맵의 시작 위치 x
			(int)(destY - (imageInfo->frameHeight / 2)),		// 복사될 비트맵의 시작 위치 y
			(int)(imageInfo->frameWidth * scale),	// 원본 복사할 가로 크기
			(int)(imageInfo->frameHeight * scale),	// 원본 복사할 세로 크기
			imageInfo->hMemDc, 	// 원본 DC
			(int)(imageInfo->frameWidth * frameX), 				// 원본 비트맵 복사 시작 위치 x
			(int)(imageInfo->frameHeight * frameY), 			// 원본 비트맵 복사 시작 위치 y
			SRCCOPY);			// 복사 옵션
	}
}
