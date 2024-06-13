#pragma once
#include "Config.h"
#include "ItemCode.h"
#define INVEN_SIZE_X 12
#define INVEN_SIZE_Y 3
class Image;
struct InventoryImage
{
	Image* img;			// 이미지
	POINTFLOAT pos;		// 실제 출력되는 좌표
	RECT rect;			// 실제 Rect
	POINT correctPos;	// 보정 좌표
};
struct Inventory
{
	int itemCode = 0;	// 아이템 코드
	int itemNum = 0;	// 아이템 갯수
	bool isOpen;		// 인벤토리 확장 여부
public:
	void Clear()
	{
		itemCode = 0;
		itemNum = 0;
	}
};
struct InventoryMouse
{
	bool inInventory;
	POINT mouse;
};
class InventoryManager : public Singleton<InventoryManager>
{
private:
	Inventory inventory[INVEN_SIZE_Y][INVEN_SIZE_X];
	InventoryImage inventoryMain;
	InventoryImage inventoryMenu;
	POINT mouse;
	POINT mouseClick;
	Image* inventoryCloseImage;
	bool isActive;

	InventoryMouse GetInventoryNum(POINT mouse);
public:
	InventoryManager();
	void Init();
	void Render(HDC hdc);
	bool Uadate();
	void Release();
public:
	void PushInventory(int itemCode, int itemNum);
	int AddInventory(int itemCode, int itemNum);
	void AddInventoryEmpty(int itemCode, int itemNum);
	bool CheckInventoryEmpty();
	void RenderItem(HDC hdc, POINT inventoryNum, POINT pos);
	bool ChangeCloseStateToOpen();
	Inventory* GetInventoryInfo(int x, int y);
};

