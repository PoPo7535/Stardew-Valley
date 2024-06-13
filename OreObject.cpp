#include "OreObject.h"
#include "Config.h"
#include "CommonFunction.h"
#include "image.h"
OreObject::OreObject(Dungeon_Tiles dungeonTiles, int x, int y)
	:frameX{ NULL }, frameY{ NULL }, dungeonTiles{}, hitAction{ 0 }, hitActionCheck{ false }
{
	this->dungeonTiles = dungeonTiles;
	pos.x = (float)x, pos.y = (float)y;
	RENDER_MANAGER->PushObjectVector(this);
	Init(); 
}
bool OreObject::InteractionPick(int damage)
{
	hp -= damage;
	hitActionCheck = true;
	if (hp <= 0)
	{
		RENDER_MANAGER->DeleteObject(this);
		CreateItem();
	}
	return false;
}

HRESULT OreObject::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Stones/Mine_Object.bmp",96,80,6,5);
	pos.x = (pos.x * 16) + 8;
	pos.y = (pos.y * 16) + 8;
	bodySize = 16;
	SetRect(&rect, pos, bodySize);
	SetStoneInfo();
	return S_OK;
}

void OreObject::Update()
{
	if (hitActionCheck)
	{
		HitAction();
	}
}

void OreObject::Render(HDC hdc)
{
	if (hp > 0)
	{
		img->Render(hdc, pos.x + hitAction - GLOBAL_POS.x, pos.y - GLOBAL_POS.y, frameX, frameY);
	}
}

void OreObject::Release()
{
	POINT result = GetPosTile(pos);
	MAP_MANAGER->DeleteMapObject(result);
	delete this;
}

void OreObject::HitAction()
{
	static float time;
	time += DELTA_TIME;
	if (time >= 0.25f)
	{
		time = 0;
		hitActionCheck = false;
	}
	else if (time >= 0.20f)
	{
		hitAction = -1;
	}
	else if (time >= 0.15f)
	{
		hitAction = +1;
	}
	else if (time >= 0.10f)
	{
		hitAction = -1;
	}
	else if (time >= 0.05f)
	{
		hitAction = +1;
	}
}

void OreObject::SetStoneInfo()
{
	int num = (rand() % 100) + 1;
	if (num > 90 && num <= 100)
	{
		frameY = 4;
		frameX = rand() % 6;
		hp = 4;
		return;
	}
	else if (num > 70 && num <= 90)
	{
		if (dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
		{
			frameY = 3;
			frameX = 0;
			hp = 2;
		}

		if (dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
		{
			frameY = 3;
			frameX = 1;
			hp = 3;
		}

		if (dungeonTiles == Dungeon_Tiles::Dungeon_Red)
		{
			frameY = 3;
			if (rand() % 5 != 5)
			{
				frameX = 2;
			}
			else
			{
				frameX = 3;
			}
			hp = 3;
		}
		return;
	}
	else if (num > 0 && num <= 70)
	{
		if (dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
		{
			if (3 != rand() % 4)
			{
				frameX = rand() % 3;
				hp = 1;
			}
			else
			{
				frameX = 2 + rand() % 2;
				hp = 2;
			}
			frameY = 0;
			return;
		}

		if (dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
		{
			if (3 != rand() % 4)
			{
				frameX = rand() % 3;
				hp = 2;
			}
			else
			{
				frameX = 2 + rand() % 2;
				hp = 3;
			}
			frameY = 1;
			return;
		}

		if (dungeonTiles == Dungeon_Tiles::Dungeon_Red)
		{
			if (3 != rand() % 4)
			{
				frameX = 1 + rand() % 4;
				hp = 3;
			}
			else
			{
				frameX = 0;
				hp = 2;
			}
			frameY = 2;
			return;
		}
	}
}

void OreObject::CreateItem()
{
	if (frameY <= 2)
	{
		ITEM_MANAGER->CreateItem(STONE, pos);
		if (rand() % 5 == 0) ITEM_MANAGER->CreateItem(COAL, pos);
		if (rand() % 5 == 0) ITEM_MANAGER->CreateItem(STONE, pos);
	}
	if (frameY == 3)
	{
		switch (frameX)
		{
		case 0:
			ITEM_MANAGER->CreateItem(COPPER, pos);
			break;
		case 1:
			ITEM_MANAGER->CreateItem(STEEL, pos);
			break;
		case 2:
			ITEM_MANAGER->CreateItem(GOLD, pos);
			break;
		case 3:
			ITEM_MANAGER->CreateItem(IRIDIUM, pos);
			break;
		}
	}
	else if (frameY == 4)
	{
		switch (frameX)
		{
		case 0:
			ITEM_MANAGER->CreateItem(AQUAMARINE, pos);
			break;
		case 1:
			ITEM_MANAGER->CreateItem(RUBY, pos);
			break;
		case 2:
			ITEM_MANAGER->CreateItem(AMETHYST, pos);
			break;
		case 3:
			ITEM_MANAGER->CreateItem(TOPAZ, pos);
			break;
		case 4:
			ITEM_MANAGER->CreateItem(EMERALD, pos);
			break;
		case 5:
			ITEM_MANAGER->CreateItem(DIAMOND, pos);
			break;
		}
	}
}
