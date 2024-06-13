#include "Shop_Blacksmith.h"
#include "Image.h"
#include "Config.h"
#include "CommonFunction.h"
HRESULT Shop_Blacksmith::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/NPC/BlackSmith.bmp", 16, 32, 1, 1);
	pos.x = (pos.x * 16) + 8;
	pos.y = (pos.y * 16) + 8;
	SetRect(&rect, pos, bodySize);
	return S_OK;
}

void Shop_Blacksmith::Update()
{

}

void Shop_Blacksmith::Render(HDC hdc)
{
	img->Render(hdc, pos.x - GLOBAL_POS.x, pos.y - GLOBAL_POS.y - 8, 0, 0);
}

void Shop_Blacksmith::Release()
{
	POINT result = GetPosTile(pos);
	MAP_MANAGER->DeleteMapObject(result);
	delete this;
}

void Shop_Blacksmith::InteractionAction()
{
	SHOP_MANAGER->ActiveShop("BlackSmith");
}

Shop_Blacksmith::Shop_Blacksmith(int x, int y)
{
	bodySize = 16;
	pos.x = (float)x, pos.y = (float)y;
	RENDER_MANAGER->PushObjectVector(this);
	Init();
}
