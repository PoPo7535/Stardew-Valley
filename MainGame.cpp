#include "MainGame.h"
#include "Image.h"
#include "ImageManager.h"
#include "CommonFunction.h"
HRESULT MainGame::Init()
{
	srand((unsigned int) time(nullptr));
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	GameDataManager::GetSingleton()->Init();
	ItemManager::GetSingleton()->Init();
	InventoryManager::GetSingleton()->Init();
	MapManager::GetSingleton()->Init();
	CamerManager::GetSingleton()->Init();
	ObjectRenderManager::GetSingleton()->Init();
	UIManager::GetSingleton()->Init();
	ShopManager::GetSingleton()->Init();
	Input::Init(g_hWnd);

	//TilemapToolScene
	//MineScene
	SetWindowSize(20, 10, WIN_SIZE_X * 3, WIN_SIZE_Y * 3);
	windowX = WIN_SIZE_X;
	windowY = WIN_SIZE_Y;
	SceneManager::GetSingleton()->ChangeScene("TopFloorScene");
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	clickedMousePosX = 0; 
	clickedMousePosY = 0; 

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init("Image/empty.bmp", 1000, 1000);

	return S_OK;
}

void MainGame::Update()
{
	Input::Update();
	TimerManager::GetSingleton()->Update();
	SceneManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();
	PatBlt(hBackBufferDC, 0, 0, backBuffer->GetWidth(), backBuffer->GetHeight(), BLACKNESS);
	SceneManager::GetSingleton()->Render(hBackBufferDC);
	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	ImageManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();
	TimerManager::GetSingleton()->Release();

	MapManager::GetSingleton()->Release();
	CamerManager::GetSingleton()->Release();
	GameDataManager::GetSingleton()->Release();
	InventoryManager::GetSingleton()->Release();
	ItemManager::GetSingleton()->Release();
	ObjectRenderManager::GetSingleton()->Release();
	ShopManager::GetSingleton()->Release();
	UIManager::GetSingleton()->Release();
	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
