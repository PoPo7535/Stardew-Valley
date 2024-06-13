#include "PlayerItemHold.h"
#include "Config.h"
PlayerItemHold::PlayerItemHold(Player* player)
	:player{ player } {}

HRESULT PlayerItemHold::Init()
{
	return S_OK;
}

void PlayerItemHold::Update()
{
}

void PlayerItemHold::Render(HDC hdc)
{
}

void PlayerItemHold::Release()
{
}

void PlayerItemHold::SelectItem(int num)
{
}
