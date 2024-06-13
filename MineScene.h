#pragma once
#include "GameEntity.h"
#include "Config.h"

class Player;
class Image;
class MineScene : public GameEntity
{
private:
	Player* player;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	MineScene() :
		player{ nullptr }
	{}
	virtual ~MineScene() = default;
};
