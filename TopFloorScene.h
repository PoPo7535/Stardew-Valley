#pragma once
#include "GameEntity.h"
class Player;
class TopFloorScene : public GameEntity
{
private:
	Player* player;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	TopFloorScene() :
		player{ nullptr }
	{}
	virtual ~TopFloorScene() = default;
};

