#include "MineScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Player.h"

HRESULT MineScene::Init()
{
    MAP_MANAGER->Load(GAMEDATA_MANAGER->GetMapNum());
    MAP_MANAGER->CreateOreObject();
    player = new Player;
    player->Init();
    RENDER_MANAGER->PushObjectVector(player);


    return S_OK;
}

void MineScene::Update()
{

    if (INVEN_MANAGER->Uadate() == true)
    {   // �κ��丮�� �����ִٸ� �ٷ� ����
        return;
    }
    player->Update();
    ITEM_MANAGER->Update();
    MAP_MANAGER->Update();
}

void MineScene::Render(HDC hdc)
{

    MAP_MANAGER->DrawMapLayer(hdc, 1);
    MAP_MANAGER->DrawMapLayer(hdc, 2);
    RENDER_MANAGER->ObjectRender(hdc);
    MAP_MANAGER->DrawMapLayer(hdc, 3);
    INVEN_MANAGER->Render(hdc);
    if (GET_KEY_STAY('G'))
    {
        MAP_MANAGER->DrawMapCollision(hdc);
    }
    UI_MANAGER->Render(hdc);
}


void MineScene::Release()
{
    SAFE_RELEASE(player);
    RENDER_MANAGER->VectorClear();
}
