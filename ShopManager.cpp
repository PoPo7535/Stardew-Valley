#include "ShopManager.h"
#include "ItemCode.h"
#include "Image.h"
#include "CommonFunction.h"
#include "ItemsToSell.h"
#include<string>

#define PORTRAIT_POS POINTFLOAT{ 76,68 }

void ShopManager::ActiveShop(string shopTypeString)
{
	if (shopTypeString == "BlackSmith")
	{
		shopType = ShopType::BlackSmith;
		isActive = true;
	}
}

ShopManager::ShopManager()
	:isActive{ false }, shopImage{}, salesListStartNum{ 0 }{};

void ShopManager::Init()
{
	shopImage.main = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Main.bmp", 356, 178, 1, 1);
	shopImage.mainPos = POINTFLOAT{ (WIN_SIZE_X / 2) ,(WIN_SIZE_Y / 2)};
	SetRect(&shopImage.mainRect, shopImage.mainPos, shopImage.main->GetWidth(), shopImage.main->GetHeight());

	shopImage.up = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_ArrowUp.bmp", 10, 11, 1, 1);
	shopImage.upPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 185 ,(WIN_SIZE_Y / 2) - 70 };
	SetRect(&shopImage.upRect, shopImage.upPos, shopImage.up->GetWidth(), shopImage.up->GetHeight());

	shopImage.down = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_ArrowDown.bmp", 10, 11, 1, 1);
	shopImage.downPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 185 ,(WIN_SIZE_Y / 2) + 15 };
	SetRect(&shopImage.downRect, shopImage.downPos, shopImage.down->GetWidth(), shopImage.down->GetHeight());

	shopImage.cancel = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Cancel.bmp", 11, 11, 1, 1);
	shopImage.cancelPos = POINTFLOAT{ (WIN_SIZE_X / 2) + 184 ,(WIN_SIZE_Y / 2) - 85 };
	SetRect(&shopImage.cancelRect, shopImage.cancelPos, shopImage.cancel->GetWidth(), shopImage.cancel->GetHeight());

	itemToSell = new ItemsToSell(this);
	itemToSell->Init();
	blackSmith.masterName = "클린트";
	blackSmith.portrait = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Portrait_Smith.bmp", 66, 66, 1, 1);
	blackSmith.portraitPos = PORTRAIT_POS;
	blackSmith.salesList = new int[8];
	blackSmith.salesListMaxNum = 8;
	blackSmith.salesList[0] = BAG;
	blackSmith.salesList[1] = NORMAL_PICK;
	blackSmith.salesList[2] = COPPER_PICK;
	blackSmith.salesList[3] = IRON_PICK;
	blackSmith.salesList[4] = GOLD_PICK;
	blackSmith.salesList[5] = COPPER;
	blackSmith.salesList[6] = STEEL;
	blackSmith.salesList[7] = GOLD;

	shopType = ShopType::None;

	coinImage = ImageManager::GetSingleton()->FindImage("Image/Shop/Shop_Coin.bmp", 11, 11, 1, 1);
}

bool ShopManager::Update()
{
	if (isActive == false) return false;

	switch (shopType)
	{
	case ShopType::BlackSmith:
		break;
	}
	if (Input::GetButtonDown(VK_LBUTTON))
	{
		if (PtInRect(&(shopImage.upRect), GetMousePoint()))
		{	// 위에버튼
			if (salesListStartNum != 0)
			{
				--salesListStartNum;
			}
		}
		else if (PtInRect(&(shopImage.downRect), GetMousePoint()))
		{	// 아래버튼
			if (salesListStartNum + 4 < blackSmith.salesListMaxNum)
			{
				++salesListStartNum;
			}
		}
		else if (PtInRect(&(shopImage.cancelRect), GetMousePoint()))
		{	// 취소버튼
			isActive = false;
		}
		else 
		{
			// 아이템 판매
			itemToSell->SellItem();

			// 아이템 구매
			itemToSell->BuyItem();
		}
	}


	return true;
}

void ShopManager::Render(HDC hdc)
{
	if (isActive == false) return;
	shopImage.main->Render(hdc, shopImage.mainPos.x, shopImage.mainPos.y, 0, 0);
	shopImage.up->Render(hdc, shopImage.upPos.x, shopImage.upPos.y, 0, 0);
	shopImage.down->Render(hdc, shopImage.downPos.x, shopImage.downPos.y, 0, 0);
	shopImage.cancel->Render(hdc, shopImage.cancelPos.x, shopImage.cancelPos.y, 0, 0);

	blackSmith.portrait->Render(hdc, blackSmith.portraitPos.x, blackSmith.portraitPos.y,0,0);

	// 플레이어 돈 출력
	int money = GAMEDATA_MANAGER->GetPlayerMoney();
	if (money != 0)
	{
		for (int i = 0; money > 0; ++i)
		{
			int number = (int)(money % 10);
			money = (int)(money / 10);
			char num_char[256];
			sprintf_s(num_char, "%d", number);
			PrintText(hdc, num_char, 169 - (i * 6), 150);
		}
	}
	else
	{
		char num_char[256];
		sprintf_s(num_char, "%d", 0);
		PrintText(hdc, num_char, 169 , 150);
	}

	itemToSell->RenderSaleslist(hdc);

	// 인벤토리 출력
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 12; ++x)
		{
			int itemCode = INVEN_MANAGER->GetInventoryInfo(x, y)->itemCode;
			INVEN_MANAGER->RenderItem(hdc, POINT{ x,y }, POINT{ 196 + (x * 16), 161 + y + (y * 16) });
		}
	}
}

POINT ShopManager::GetInventoryNum()
{
	POINT inventoryNum{ -1,-1 };
	POINT mouse = GetMousePoint();
	const static POINTFLOAT inventoryPos = { shopImage.mainPos.x + 74,shopImage.mainPos.y + 58 };
	const static RECT inventoryRect
	{
		(LONG)inventoryPos.x - ((TILE_SIZE * INVEN_SIZE_X) / 2),
		(LONG)inventoryPos.y - ((TILE_SIZE * INVEN_SIZE_Y) / 2),
		(LONG)inventoryPos.x + ((TILE_SIZE * INVEN_SIZE_X) / 2),
		(LONG)inventoryPos.y + ((TILE_SIZE * INVEN_SIZE_Y) / 2)
	};

	if (PtInRect(&inventoryRect, mouse))
	{
		mouse.x -= inventoryRect.left;
		mouse.y -= inventoryRect.top;
		if (0 <= mouse.x && mouse.x <= (TILE_SIZE * INVEN_SIZE_X))
		{
			inventoryNum.x = (LONG)(mouse.x / TILE_SIZE);
		}
		if (0 <= mouse.y && mouse.y <= (TILE_SIZE * INVEN_SIZE_Y))
		{
			inventoryNum.y = (LONG)(mouse.y / TILE_SIZE);
		}
	}
	return inventoryNum;
}

int ShopManager::GetShopSoldNum()
{
	POINT mouse = GetMousePoint();
	int num = -1;
	const static POINTFLOAT shopPos = { shopImage.mainPos.x + 44,shopImage.mainPos.y - 33 };
	const static RECT shopRect
	{
		(LONG)shopPos.x - (258 / 2),
		(LONG)shopPos.y - ((26 * 4) / 2),
		(LONG)shopPos.x + (258 / 2),
		(LONG)shopPos.y + ((26 * 4) / 2)
	};
	if (PtInRect(&shopRect, mouse))
	{
		mouse.x -= shopRect.left;
		mouse.y -= shopRect.top;
		if (0 <= mouse.y && mouse.y <= (26 * 4))
		{
			num = (LONG)(mouse.y / 26);
		}
	}
	cout << num << "\n";
	return num;
}

void ShopManager::Release()
{
	delete[] blackSmith.salesList;
	blackSmith.salesList = nullptr;

	SAFE_RELEASE(itemToSell);
	ReleaseSingleton();
}
