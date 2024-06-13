#include "UIManager.h"
#include "Image.h"
#include "Config.h"
UIManager::UIManager()
	:playerInventoryUI{} {}
HRESULT UIManager::Init()
{
	playerInventoryUI = new PlayerInventoryUI;
	playerInventoryUI->Init();
	return S_OK;
}

void UIManager::Update()
{
	playerInventoryUI->Update();
}

void UIManager::Render(HDC hdc)
{
	playerInventoryUI->Render(hdc);
	
}

void UIManager::Release()
{
	SAFE_RELEASE(playerInventoryUI);
	ReleaseSingleton();
}

int UIManager::GetSelectItemNum()
{
	return playerInventoryUI->GetSelectItemNum();
}

void UIManager::SetSelectItemNum(int num)
{
	playerInventoryUI->SetSelectItemNum(num);
}

