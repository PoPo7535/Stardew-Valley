#pragma once
#include "Config.h"

class Image;
struct UIImage
{
	Image* inventory;
	POINT inventoryPos;
	Image* inventorySelect;
	POINT inventorySelectPos;
};
class PlayerInventoryUI
{
private:
	UIImage uiImage;
	int SelectItem;
public:
	PlayerInventoryUI();
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetSelectItemNum(int num) { SelectItem = num; }
	int GetSelectItemNum() { return SelectItem; }
};

