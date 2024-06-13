#pragma once
#include "Singleton.h"
class CamerManager : public Singleton<CamerManager>
{
private:
	POINTFLOAT globalPos;
	int mapSizeX, mapSizeY;
	int tileSize;
public:
	CamerManager():
		globalPos{},
		tileSize{16},
		mapSizeX{ NULL }, mapSizeY{ NULL } {}
	void Init() {}
public:
	inline void SetMapSize(int x, int y) 
	{ 
		mapSizeX = x * tileSize;
		mapSizeY = y * tileSize;
	}
	inline void SetGlobalPos(POINTFLOAT playerPos)
	{
		if (WIN_SIZE_X > mapSizeX)
		{	// ���� ��ũ�Ⱑ ������ â ���� ���� ���
			globalPos.x = -(float)((WIN_SIZE_X - mapSizeX) / 2);
		} 
		else
		{	// ���� ��ũ�Ⱑ ������ â���� Ŭ ��� 
			if ((WIN_SIZE_X / 2) <= playerPos.x && playerPos.x <= mapSizeX - (WIN_SIZE_X / 2))
			{	// �÷��̾��� ��ġ�� ���ʰ� ������ ������ ����
				globalPos.x = playerPos.x - (WIN_SIZE_X / 2);
			}
			else if ((WIN_SIZE_X / 2) > playerPos.x)
			{	// �÷��̾��� ��ġ�� ���ʿ� ��������
				globalPos.x = 0;
			}
			else if (mapSizeX - (WIN_SIZE_X / 2) < playerPos.x)
			{	// �÷��̾��� ��ġ�� �����ʿ� ��������
				globalPos.x = (float)mapSizeX - WIN_SIZE_X;
			}
		}
		if (WIN_SIZE_Y > mapSizeY)
		{	// ���� ��ũ�Ⱑ ������ â ���� ���� ���
			globalPos.y = -(float)((WIN_SIZE_Y - mapSizeY) / 2);
		}
		else
		{	// ���� ��ũ�Ⱑ ������ â���� Ŭ ��� 
			if ((WIN_SIZE_Y / 2) <= playerPos.y && playerPos.y <= mapSizeY - (WIN_SIZE_Y / 2))
			{	// �÷��̾��� ��ġ�� ���� �Ʒ��� ������ ����
				globalPos.y = playerPos.y - (WIN_SIZE_Y / 2);
			}
			else if ((WIN_SIZE_Y / 2) > playerPos.y)
			{	// �÷��̾��� ��ġ�� ���� ��������
				globalPos.y = 0;
			}
			else if (mapSizeY - (WIN_SIZE_Y / 2) < playerPos.y)
			{	// �÷��̾��� ��ġ�� �Ʒ��� ��������
				globalPos.y = (float)mapSizeY - WIN_SIZE_Y;
			}
		}
	}
	inline POINTFLOAT GetGlobalPos() { return globalPos; }

	inline void Release() { ReleaseSingleton(); };
};