#pragma once
#include "GameEntity.h"
#include "Config.h"

class Image;
class BattleScene : public GameEntity
{
private:
	Image* selectDungeon;
	int mapPosX, mapPosY;
	int mapPrintX, mapPrintY;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;	// 오버로딩
	virtual void Release() override;
	BattleScene():
		selectDungeon{nullptr},
		mapPosX{NULL} , mapPosY{NULL},
		mapPrintX{ 20 }, mapPrintY{ 20 }
	{}
	virtual ~BattleScene() = default;
	int Load(int num = 1);
};

