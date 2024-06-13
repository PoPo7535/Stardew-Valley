#pragma once
#include "GameEntity.h"
#include "Config.h"
#include "MapInfo.h"
#include <vector>

typedef struct tagSampleTile
{
	tagSampleTile() :
		rc{ }, frameX{ NULL }, frameY{ NULL }
	{};
	RECT rc;
	int frameX, frameY;
} SAMPLE_TILE_INFO;

struct Layer
{
	Layer() :
		numImage{ nullptr }, num{ 0 }, modeImage{ nullptr }, mode{ 0 }
	{}
	Image* numImage;	//	Ÿ���� ���̾� �ѹ� �̹���
	int num;			//	Ÿ���� ���̾� �ѹ�
	Image* modeImage;	//	Ÿ���� ���̾� ��� ��� �̹���
	int mode;			//	Ÿ���� ���̾� ��� ���
};

class Image;
class TilemapToolScene : public GameEntity
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	TilemapToolScene();
	virtual ~TilemapToolScene() = default;
	void Save();
	void BackUpSave();
	void Load();

private:
	HPEN pen, oPen;
	SAMPLE_TILE_INFO sampleTileInfo[18][16];	//	���� Ÿ��
	SAMPLE_TILE_INFO selectedSampleTile;		//	���õ� ����Ÿ��
	int sampleTileWidth, sampleTileHeight;		// ���õ� ����Ÿ���� �ʺ�� ����
	
	Image* mineImage[9];
	Image* selectMineImage;	//==============

	Layer layer;

	Image* tileStateImage;	//  �� Ÿ���� ���� �̹���
	Tile_State tileState;	//  �� Ÿ���� ����(������)

	POINT mouse;			//	���콺 ��ġ

	MAP_INFO mapInfoTemp;		// ������ �� ����
	MAP_INFO mapInfo;
	//MAP_INFO2 mapInfo2;
	int mapPrintX, mapPrintY;	// �� ��� ����
	int mapPosX, mapPosY;		// ���� ���� �� ��ġ
	float backUpTime;
	int backUpNum;
};

