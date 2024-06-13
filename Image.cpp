#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);		// ������ ������ ���� ��������

	// �� ��Ʈ�� ����
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = ImageLoadType::Empty;
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// ���� ������ DC 
											// �⺻������ Bitmap�� ����Ǿ� �ִ�.
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDc, imageInfo->hBitmap);

	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)	// ��Ʈ�� ������ �������� ��
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
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// ���� ������ DC 
											// �⺻������ Bitmap�� ����Ǿ� �ִ�.
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
	imageInfo->hMemDc = CreateCompatibleDC(hdc);	// ���� ������ DC 
											// �⺻������ Bitmap�� ����Ǿ� �ִ�.
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
	BitBlt(hdc,				// ���� ������ DC
		destX,					// ����� ��Ʈ���� ���� ��ġ x
		destY,					// ����� ��Ʈ���� ���� ��ġ y
		imageInfo->width,	// ���� ������ ���� ũ��
		imageInfo->height,	// ���� ������ ���� ũ��
		imageInfo->hMemDc,	// ���� DC
		0,					// ���� ��Ʈ�� ���� ���� ��ġ x
		0,					// ���� ��Ʈ�� ���� ���� ��ġ y
		SRCCOPY);			// ���� �ɼ�
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
			(int)(imageInfo->frameHeight * scale),	// ��ü ������ ��

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
		BitBlt(hdc,				// ���� ������ DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// ����� ��Ʈ���� ���� ��ġ x
			(int)(destY - (imageInfo->frameHeight / 2)),		// ����� ��Ʈ���� ���� ��ġ y
			(int)(imageInfo->frameWidth * scale),	// ���� ������ ���� ũ��
			(int)(imageInfo->frameHeight * scale),	// ���� ������ ���� ũ��
			imageInfo->hMemDc,	// ���� DC
			(int)(imageInfo->frameWidth * frameX),				// ���� ��Ʈ�� ���� ���� ��ġ x
			(int)(imageInfo->frameHeight * frameY),			// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
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
			(int)(imageInfo->frameHeight * scale),	// ��ü ������ ��

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
		BitBlt(hdc,				// ���� ������ DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// ����� ��Ʈ���� ���� ��ġ x
			(int)(destY - (imageInfo->frameHeight / 2)),		// ����� ��Ʈ���� ���� ��ġ y
			(int)(imageInfo->frameWidth * scale),	// ���� ������ ���� ũ��
			(int)(imageInfo->frameHeight * scale),	// ���� ������ ���� ũ��
			imageInfo->hMemDc, 	// ���� DC
			(int)(imageInfo->frameWidth * frameX), 				// ���� ��Ʈ�� ���� ���� ��ġ x
			(int)(imageInfo->frameHeight * frameY), 			// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
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
			(int)(imageInfo->frameHeight * scale),	// ��ü ������ ��

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
		BitBlt(hdc,				// ���� ������ DC
			(int)(destX - (imageInfo->frameWidth / 2)),		// ����� ��Ʈ���� ���� ��ġ x
			(int)(destY - (imageInfo->frameHeight / 2)),		// ����� ��Ʈ���� ���� ��ġ y
			(int)(imageInfo->frameWidth * scale),	// ���� ������ ���� ũ��
			(int)(imageInfo->frameHeight * scale),	// ���� ������ ���� ũ��
			imageInfo->hMemDc, 	// ���� DC
			(int)(imageInfo->frameWidth * frameX), 				// ���� ��Ʈ�� ���� ���� ��ġ x
			(int)(imageInfo->frameHeight * frameY), 			// ���� ��Ʈ�� ���� ���� ��ġ y
			SRCCOPY);			// ���� �ɼ�
	}
}
