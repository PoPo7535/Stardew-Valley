#pragma once
#include "GameEntity.h"
class Player;
class Image;
class PlayerStateMove : public GameEntity
{
private:
	Player* player;
	Image* img;
	float frameTime;
	int frame;
	void Move(float posX, float posY);
	void MovePlayer();

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	bool CheckAction();
	PlayerStateMove(Player* player);
	virtual ~PlayerStateMove() = default;

public:
};

