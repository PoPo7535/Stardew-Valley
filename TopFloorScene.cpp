#include "TopFloorScene.h"
#include "Config.h"
#include "Player.h"
#include "Shop_Blacksmith.h"
HRESULT TopFloorScene::Init()
{
    MAP_MANAGER->Load(GAMEDATA_MANAGER->GetMapNum());
    player = new Player;
    player->Init();
    RENDER_MANAGER->PushObjectVector(player);
    MAP_MANAGER->CreateObject(new Shop_Blacksmith(4, 4), POINT{ 4,4 });
	return S_OK;
}

void TopFloorScene::Update()
{
    if (SHOP_MANAGER->Update() == true)
    {
        return;
    }
    if (INVEN_MANAGER->Uadate() == true)
    {   // 인벤토리가 열려있다면 바로 리턴
        return;
    }

    player->Update();
    ITEM_MANAGER->Update();
    MAP_MANAGER->Update();
}

void TopFloorScene::Render(HDC hdc)
{
    MAP_MANAGER->DrawMapLayer(hdc, 1);
    MAP_MANAGER->DrawMapLayer(hdc, 2);
    RENDER_MANAGER->ObjectRender(hdc);
    MAP_MANAGER->DrawMapLayer(hdc, 3);
    INVEN_MANAGER->Render(hdc);
    UI_MANAGER->Render(hdc);
    SHOP_MANAGER->Render(hdc);
}

void TopFloorScene::Release()
{
    SAFE_RELEASE(player);
    RENDER_MANAGER->VectorClear();
}
