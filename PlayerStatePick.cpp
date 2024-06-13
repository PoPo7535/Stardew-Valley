#include "PlayerStatePick.h"
#include "Player.h"
#include "Image.h"
#include "Config.h"
HRESULT PlayerStatePick::Init()
{
	img.normal = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Normal.bmp", 240, 192, 5, 4);
	img.copper = ImageManager::GetSingleton()->FindImage("Image/Player/Player_CopperPick_Action.bmp", 240, 192, 5, 4);
	img.iron = ImageManager::GetSingleton()->FindImage("Image/Player/Player_IronPick_Action.bmp", 240, 192, 5, 4);
	img.gold = ImageManager::GetSingleton()->FindImage("Image/Player/Player_GoldPick_Action.bmp", 240, 192, 5, 4);
	return S_OK;
}

void PlayerStatePick::Update()
{
	frameTime += DELTA_TIME;
	if (frameTime > 0.1f)
	{
		frameTime -= 0.1f;
		++frame;
	}
	itemCode = INVEN_MANAGER->GetInventoryInfo(UI_MANAGER->GetSelectItemNum(), 0)->itemCode;
	CheckAction();
}

void PlayerStatePick::Render(HDC hdc)
{
	if (itemCode == NORMAL_PICK)
	{
		img.normal->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y - 8,
			frame,
			player->playerDirection);
	}
	else if (itemCode == COPPER_PICK)
	{
		img.copper->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y - 8,
			frame,
			player->playerDirection);
	}
	else if (itemCode == IRON_PICK)
	{
		img.iron->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y - 8,
			frame,
			player->playerDirection);
	}
	else if (itemCode == GOLD_PICK)
	{
		img.gold->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y - 8,
			frame,
			player->playerDirection);
	}
}

void PlayerStatePick::Release() {}

bool PlayerStatePick::CheckAction()
{
	if (frame >= 5)
	{
		frame = 0;
		frameTime = 0.0f;
		POINT result = player->GetFrontTilePos();
		if (MAP->object[result.y][result.x] != nullptr)
		{
			MAP->object[result.y][result.x]->InteractionPick(itemCode - 13);
		}
		player->playerState = PlayerState::Idle;
	}
	return false;
}

PlayerStatePick::PlayerStatePick(Player* player)
	:player{ player }, img{ nullptr }, frameTime{ 0.0f }, frame{ 0 }{};