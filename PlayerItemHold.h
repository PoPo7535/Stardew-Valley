#pragma once
#include "GameEntity.h"
class Player;
class PlayerItemHold : public GameEntity
{
private:
	Player* player;
public:
	PlayerItemHold(Player* player);
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void SelectItem(int num);
};

