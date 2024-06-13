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
	Image* numImage;	//	타일의 레이어 넘버 이미지
	int num;			//	타일의 레이어 넘버
	Image* modeImage;	//	타일의 레이어 출력 모드 이미지
	int mode;			//	타일의 레이어 출력 모드
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
	SAMPLE_TILE_INFO sampleTileInfo[18][16];	//	샘플 타일
	SAMPLE_TILE_INFO selectedSampleTile;		//	선택된 샘플타일
	int sampleTileWidth, sampleTileHeight;		// 선택된 샘플타일의 너비와 높이
	
	Image* mineImage[9];
	Image* selectMineImage;	//==============

	Layer layer;

	Image* tileStateImage;	//  맵 타일의 상태 이미지
	Tile_State tileState;	//  맵 타일의 상태(열거형)

	POINT mouse;			//	마우스 위치

	MAP_INFO mapInfoTemp;		// 저장할 맵 템프
	MAP_INFO mapInfo;
	//MAP_INFO2 mapInfo2;
	int mapPrintX, mapPrintY;	// 맵 출력 범위
	int mapPosX, mapPosY;		// 현재 보는 맵 위치
	float backUpTime;
	int backUpNum;
};

