#pragma once
#include "GameEntity.h"
class Player;
class Image;
class PlayerStateIdel : public GameEntity
{
private:
	Player* player;
	Image* img;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	PlayerStateIdel(Player* player);
	virtual ~PlayerStateIdel();
};

