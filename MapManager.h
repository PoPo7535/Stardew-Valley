#pragma once
#include "Config.h"
#include "MapInfo.h"
#include "GameObject.h"
class Interaction;
class Image;
class MapManager : public Singleton<MapManager>
{
private:
	MAP_INFO mapInfo;
	Image* selectDungeon;
	vector<POINT> exit;
	bool ladderDownCheck;
	HPEN pen, oPen;

public:
	MapManager();
	void Init();
	void Update();
	void Release();
public:
	void DrawMapLayer(HDC hdc, int LayerNum);
	// �� �׸���

	void ClearObject();
	void Clear();
	
	const MAP_INFO* GetMap() { return &mapInfo; }
	
	// �ʿ� �ִ� ������Ʈ ����
	void DeleteMapObject(POINT pos);

	// ������Ʈ ����
	void CreateObject(Interaction* object,POINT pos);

	// ��ȣ�ۿ�
	void Interactions(POINT pos);

	void SetDungeonImage();
	void Load(int num);
	
	void DrawMapCollision(HDC hdc);

	// �ʿ� ������Ʈ ����
	void CreateOreObject();

	
};

