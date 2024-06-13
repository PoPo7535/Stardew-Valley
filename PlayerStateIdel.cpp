#include "PlayerStateIdel.h"
#include "Config.h"
#include "Image.h"
#include "Player.h"
HRESULT PlayerStateIdel::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Normal.bmp", 16, 128, 1, 4);
	return S_OK;
}

void PlayerStateIdel::Update()
{
}

void PlayerStateIdel::Render(HDC hdc)
{
	img->Render(hdc,
		player->pos.x - GLOBAL_POS.x,
		player->pos.y - player->bodySize - GLOBAL_POS.y,
		0,
		player->playerDirection);
}

void PlayerStateIdel::Release()
{
}

PlayerStateIdel::PlayerStateIdel(Player* player)
	:player{player},img{nullptr}
{}

PlayerStateIdel::~PlayerStateIdel()
{
}
