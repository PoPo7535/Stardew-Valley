#include "ImageManager.h"
#include "Image.h"

void ImageManager::Init()
{
}

void ImageManager::Release()
{
	for (map<string, Image*>::iterator it = mapImages.begin(); it != mapImages.end(); /*it++*/)
	{
		SAFE_RELEASE(it->second);
		it = mapImages.erase(it);	// ���� ������ �ּ�(iterator)�� ���ŵȴ�.
	}
	mapImages.clear();
	this->ReleaseSingleton();
}

//void ImageManager::AddImage()
//{
//	// �߰��Ϸ��� �̹����� �ڷᱸ������ ã�´�.
//
//	// ������ ����.
//
//	// ������ �߰��Ѵ�.
//	//new Image();
//	//img->Init
//
//}

Image* ImageManager::AddImage(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::AddImage(const char* fileName, int width, int height, 
	int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{

	Image* img = new Image;
	if (FAILED(img->Init(fileName, width, height, maxFrameX, 
		maxFrameY, isTrans, transColor)))
	{
		SAFE_RELEASE(img);
		return nullptr;
	}

	mapImages.insert(make_pair(fileName, img));

	return img;
}

Image* ImageManager::FindImage(const char* fileName, int width, int height,
	int maxFrameX, int maxFrameY)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return AddImage(fileName, width, height, maxFrameX, maxFrameY,true,RGB(255,0,255));
	}

	return it->second;
}

void ImageManager::DeleteImage(const char* fileName)
{
	map<string, Image*>::iterator it = mapImages.find(fileName);
	if (it == mapImages.end())
	{
		return;
	}

	SAFE_RELEASE(it->second);	// Image*	// Image �����Ҵ� ����
	mapImages.erase(it);		// �ʿ��� ��� ����
}
