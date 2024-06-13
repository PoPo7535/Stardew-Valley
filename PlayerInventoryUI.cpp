#include "PlayerInventoryUI.h"
#include "Image.h"
#include "Config.h"
#define SPACE 4

PlayerInventoryUI::PlayerInventoryUI()
	:uiImage{}, SelectItem{ 0 }{}

HRESULT PlayerInventoryUI::Init()
{
	uiImage.inventory = ImageManager::GetSingleton()->FindImage("Image/UI/Inventory.bmp", 200, 24, 1, 1);
	uiImage.inventoryPos.x = (WIN_SIZE_X / 2);
	uiImage.inventoryPos.y = WIN_SIZE_Y - (uiImage.inventory->GetFrameHeight() / 2) - SPACE;

	uiImage.inventorySelect = ImageManager::GetSingleton()->FindImage("Image/UI/InventorySelect.bmp", 16, 16, 1, 1);
	uiImage.inventorySelectPos.x = (WIN_SIZE_X / 2) + SPACE -
		(uiImage.inventory->GetFrameWidth() / 2) + (uiImage.inventorySelect->GetFrameWidth() / 2);
	uiImage.inventorySelectPos.y = WIN_SIZE_Y - (uiImage.inventorySelect->GetFrameHeight() / 2) - (SPACE * 2);
	return S_OK;
}

void PlayerInventoryUI::Update()
{
}

void PlayerInventoryUI::Render(HDC hdc)
{
	// 하단 인벤토리 UI
	uiImage.inventory->Render(hdc,
		uiImage.inventoryPos.x,
		uiImage.inventoryPos.y,
		0, 0);
	
	// 선택한 아이템
	uiImage.inventorySelect->Render(hdc,
		uiImage.inventorySelectPos.x + (TILE_SIZE * SelectItem),
		uiImage.inventorySelectPos.y,
		0, 0);

	// 아이템
	const static POINT renderItemPos{
		uiImage.inventoryPos.x - (uiImage.inventory->GetWidth() / 2),
		uiImage.inventoryPos.y };
	for (int i = 0; i < 12; ++i)
	{
		INVEN_MANAGER->RenderItem(hdc, POINT{ i,0 }, POINT{ renderItemPos.x + 12 + (16 * i),renderItemPos.y });
	}
}

void PlayerInventoryUI::Release()
{
}
