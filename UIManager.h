#pragma once
#include "Config.h"
#include "PlayerInventoryUI.h"

class PlayerInventoryUI;
class UIManager : public Singleton<UIManager>
{
private:
	PlayerInventoryUI* playerInventoryUI;
public:
	UIManager();
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SetSelectItemNum(int num);
	int GetSelectItemNum();
};

