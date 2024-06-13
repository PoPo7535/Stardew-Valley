#include "Item.h"
#include "Image.h"
#include "Config.h"
bool Item::FollowPlayer()
{
	POINTFLOAT playerPos;
	float distance;

	playerPos = GAMEDATA_MANAGER->GetPlayerPos();
	distance = (float)sqrt(pow(pos.x - playerPos.x, 2) + pow(pos.y - playerPos.y, 2));
	// 플레이어까지 직선거리

	if (distance < 30.0f)
	{
		pos.x -= (playerPos.x - pos.x) * (distance - 30) * 0.2f * DELTA_TIME;
		pos.y -= (playerPos.y - pos.y) * (distance - 30) * 0.2f * DELTA_TIME;
	}
	// 플레이어까지의 거리가 30 이하라면 플레이어 추적

	if (distance < 5.0f)
	{
		return true;
	}

	return false;
}

void Item::GravityAction()
{
	bool xCheck = move.speed.x > 0.0f ? true : false;
	if (xCheck)
	{
		if (fabs(move.speed.x) > 0.1f)
		{
			move.speed.x -= 8 * DELTA_TIME;
			pos.x += move.speed.x * DELTA_TIME;
		}
	}
	else
	{
		if (fabs(move.speed.x) > 0.1f)
		{
			move.speed.x += 8 * DELTA_TIME;
			pos.x += move.speed.x * DELTA_TIME;
		}
	}

	if (!(move.landPos <= pos.y && fabs(move.speed.y) < 30) && move.gravityCheck)
	{
		move.speed.y += move.gravity * DELTA_TIME;
		if (move.landPos <= pos.y && move.speed.y >= 30)
		{
			move.speed.y *= -0.7f;
		}
		pos.y += move.speed.y * DELTA_TIME;
	}
	else
	{
		move.gravityCheck = false;
	}
}

HRESULT Item::Init()
{
	Dungeon_Tiles::Dungeon_Soil;
	move.landPos = pos.y + 2;
	
	move.speed.x = (float)(10 + (rand() % 10));
	move.speed.y = (float)((60 + (rand() % 10))*-1);
	if (rand() % 2) { move.speed.x *= -1; }
	move.gravity = 200.0f;
	return S_OK;
}

void Item::Update()
{
	GravityAction();
	if (move.time > 0.4f)
	{
		if (FollowPlayer())
		{
			INVEN_MANAGER->PushInventory(itemCode, itemNum);
			ITEM_MANAGER->DeleteObject(this);
			RENDER_MANAGER->DeleteObject(this);
			return;
		}
	}
	else
	{
		move.time += DELTA_TIME;
	}
}

void Item::Render(HDC hdc)
{
	ITEM_MANAGER->ItemRender(hdc, itemCode, (int)(pos.x - GLOBAL_POS.x), (int)(pos.y - GLOBAL_POS.y));
}

void Item::Release()
{
}

Item::Item(int key, POINTFLOAT pos, int itemNum) :
	itemCode{ key }, itemNum{ itemNum }
{
	this->pos = pos;
	Init();
	RENDER_MANAGER->PushObjectVector(this);
};
