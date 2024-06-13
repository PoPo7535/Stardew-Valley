#include "InventoryManager.h"
#include "CommonFunction.h"
#include "Image.h"

#define SPACE_X 10
#define SPACE_Y 10

InventoryMouse InventoryManager::GetInventoryNum(POINT mouse)
{
	bool check = false;
	POINT num{ -1,-1 };
	if (PtInRect(&(inventoryMain.rect), mouse))
	{	// 인벤토리 메인영역일 경우
		mouse.x -= inventoryMain.correctPos.x;
		mouse.y -= inventoryMain.correctPos.y;
		if (SPACE_X <= mouse.x && mouse.x <= SPACE_X + (TILE_SIZE * INVEN_SIZE_X))
		{
			num.x = (LONG)(mouse.x - SPACE_X) / 16;
		}
		if (SPACE_Y <= mouse.y && mouse.y <= SPACE_Y + TILE_SIZE)
		{
			num.y = 0;
		}
		else if (SPACE_Y + TILE_SIZE + 4 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 2) + 4)
		{
			num.y = 1;
		}
		else if (SPACE_Y + (TILE_SIZE * 2) + 5 <= mouse.y && mouse.y <= SPACE_Y + (TILE_SIZE * 3) + 5)
		{
			num.y = 2;
		}
		check = true;
	}
	return InventoryMouse{ check, num };
}
InventoryManager::InventoryManager()
	:inventory{}, inventoryMain{}, inventoryMenu{}, mouseClick{ -1,-1 }, isActive{ false }
{ }

void InventoryManager::PushInventory(int itemCode, int itemNum)
{
	itemNum = AddInventory(itemCode, itemNum);
	if (itemNum > 0)
	{
		AddInventoryEmpty(itemCode, itemNum);
	}
}

int InventoryManager::AddInventory(int itemCode, int itemNum)
{
	// 같은 종류의 아이템이 인벤토리에 있고, 최대갯수보다 적다면 갯수추가
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].itemCode == itemCode &&
				inventory[y][x].itemNum < 64)
			{
				inventory[y][x].itemNum += itemNum;
				if (inventory[y][x].itemNum >= 64)
				{
					itemNum = inventory[y][x].itemNum - 64;
					inventory[y][x].itemNum -= itemNum;
				}
				else
				{
					return 0;
				}
			}	
		}
	}
	return itemNum;
}

void InventoryManager::AddInventoryEmpty(int itemCode, int itemNum)
{	// 비어있는 곳에 아이템을 추가하고, 그 위치 반환
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].itemCode == 0 && inventory[y][x].isOpen == true)
			{
				inventory[y][x].itemCode = itemCode;
				inventory[y][x].itemNum = itemNum;
				inventory[y][x].itemCode = itemCode;
				return;
			}
		}
	}	
	
	// 비어있는 아이템을 칸을 찾지 못했다면
	ITEM_MANAGER->CreateItem(itemCode, GAMEDATA_MANAGER->GetPlayerPos(), itemNum);
}

bool InventoryManager::CheckInventoryEmpty()
{
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].itemCode == 0)
			{
				return true;
			}
		}
	}
	return false;
}

void InventoryManager::RenderItem(HDC hdc, POINT inventoryNum, POINT pos)
{
	// 인벤토리가 확장된 상태가 아니라면
	if (inventory[inventoryNum.y][inventoryNum.x].isOpen == false)
	{
		inventoryCloseImage->Render(hdc, pos.x, pos.y, 0, 0);
		return;
	}

	int itemCode = inventory[inventoryNum.y][inventoryNum.x].itemCode;
	if (itemCode == 0)
	{
		return;
	}
	ITEM_MANAGER->ItemRender(hdc, itemCode, pos.x-1, pos.y);

	// 아이템 갯수 출력
	int number = inventory[inventoryNum.y][inventoryNum.x].itemNum;
	if (number != 0)
	{
		char num_char[10 + sizeof(char)];
		sprintf_s(num_char, "%d", number);
		PrintText(hdc, num_char, pos.x, pos.y);
	}
}

/// <summary> 인벤토리의 닫혀있는 칸을 열림상태로 변경한다. 열림상태로 변경에 성공했다면 true를 반환한다 </summary>
bool InventoryManager::ChangeCloseStateToOpen()
{
	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (inventory[y][x].isOpen == false)
			{
				inventory[y][x].isOpen = true;
				return true;
			}
		}
	}
	return false;
}

Inventory* InventoryManager::GetInventoryInfo(int x, int y)
{
	return &inventory[y][x];
}


void InventoryManager::Init()
{
	inventoryMain.img = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Main.bmp", 213, 146, 1, 1);
	inventoryMain.pos.x = (WIN_SIZE_X / 2); inventoryMain.pos.y = (WIN_SIZE_Y / 2);
	inventoryMain.correctPos.x = (LONG)(inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2));
	inventoryMain.correctPos.y = (LONG)(inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2));
	SetRect(&inventoryMain.rect,inventoryMain.pos, 
		(inventoryMain.img->GetFrameWidth()), (inventoryMain.img->GetFrameHeight()));

	inventoryCloseImage = ImageManager::GetSingleton()->FindImage("Image/Inventory/Inventory_Close.bmp", 16, 16, 1, 1);


	for (int i = 0; i < INVEN_SIZE_X; ++i)
	{
		inventory[0][i].isOpen = true;
		inventory[0][i].isOpen = true;
		inventory[1][i].isOpen = false;
		inventory[2][i].isOpen = false;
	}
	inventory[0][0].isOpen = true;
	inventory[0][1].isOpen = true;
	PushInventory(NORMAL_PICK, 1);
}

bool InventoryManager::Uadate()
{
	if (GET_KEY_DOWN('E'))isActive = !isActive;
	if (isActive == false) return false;
	mouse = GetMousePoint();

	if (GET_KEY_DOWN(VK_LBUTTON))
	{
		mouseClick = GetInventoryNum(mouse).mouse;
	}

	return true;
}

void InventoryManager::Render(HDC hdc)
{
	if (isActive == false) return;

	// 인벤토리 메인창 렌더
	inventoryMain.img->Render(hdc,
		inventoryMain.pos.x, 
		inventoryMain.pos.y,
		0,0);
	

	for (int y = 0; y < INVEN_SIZE_Y; ++y)
	{
		for (int x = 0; x < INVEN_SIZE_X; ++x)
		{
			if (mouseClick.x == x && mouseClick.y == y)
			{	// 마우스가 인벤토리 아이템을 클릭한 경우 일때 출력 안함
				continue;
			}
			// 아이템 출력
			int space = y >= 1 ? 4 : 0;
			int posX = (int)inventoryMain.pos.x - (inventoryMain.img->GetFrameWidth() / 2) + SPACE_X + (x * TILE_SIZE) + 9;
			int posY = (int)inventoryMain.pos.y - (inventoryMain.img->GetFrameHeight() / 2) + SPACE_Y + (y * TILE_SIZE) + 8 + space;
			RenderItem(hdc, POINT{ x, y }, POINT{ posX, posY });
		}
	}

	if (mouseClick.x != -1 && mouseClick.y != -1)
	{	// 마우스가 클릭, 드래그한 인벤토리 아이템 출력
		int itemCode = inventory[mouseClick.y][mouseClick.x].itemCode;
		RenderItem(hdc, mouseClick, mouse);
	}
	
	if (GET_KEY_UP(VK_LBUTTON) && mouseClick.x >= 0 && mouseClick.y >= 0)
	{
		InventoryMouse result = GetInventoryNum(mouse);
		if (result.inInventory == false)
		{	// 마우스로 아이템을 끌어다 놓은곳이 인벤창 밖이라면
			ITEM_MANAGER->CreateItem(
				inventory[mouseClick.y][mouseClick.x].itemCode,
				GAMEDATA_MANAGER->GetPlayerPos(), 
				inventory[mouseClick.y][mouseClick.x].itemNum);

			inventory[mouseClick.y][mouseClick.x].itemCode = 0;
			inventory[mouseClick.y][mouseClick.x].itemNum = 0;
		}
		else if (result.mouse.x >= 0 && result.mouse.y >= 0)
		{	// 마우스로 아이템을 끌어다 놓은곳이 인벤창 안 이라면 스왑
			if (inventory[mouseClick.y][mouseClick.x].isOpen == true && inventory[result.mouse.y][result.mouse.x].isOpen == true)
			{
				swap(inventory[mouseClick.y][mouseClick.x], inventory[result.mouse.y][result.mouse.x]);
			}
		}
		mouseClick = { -1,-1 };
	}
}

void InventoryManager::Release()
{
	ReleaseSingleton();
}
