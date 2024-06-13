#pragma once
#include "GameEntity.h"
class Player;
class Image;
struct pickActionImage
{
	Image* normal;
	Image* copper;
	Image* iron;
	Image* gold;
};
class PlayerStatePick : public GameEntity
{
private:
	pickActionImage img;
	Player* player;
	float frameTime;
	int frame;
	int itemCode;
protected:
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	bool CheckAction();
	PlayerStatePick(Player* player);
	virtual ~PlayerStatePick() = default;

public:

};

