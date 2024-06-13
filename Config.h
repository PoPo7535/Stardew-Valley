#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")
#define WIN_START_POS_X	400
#define WIN_START_POS_Y	100
#define WIN_SIZE_X	420			// 16 * 16
#define WIN_SIZE_Y	240			// 16 * 14
#define TILEMAPTOOL_SIZE_X	620
#define TILEMAPTOOL_SIZE_Y	330
#define PIXELMAP_SIZE_X	800
#define PIXELMAP_SIZE_Y	600
#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)	{ if (p) { delete p; p = nullptr; } }
#define COUT cout << "Check" << "\n"

#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
//enum class MoveDir { Left, Right, Up, Down };

typedef struct ArgumentFuncPtr
{
	string sceneName;
	string loadingSceneName;
} ARGUMENT_PTR, *LPARGUMENT_PTR;

#include "TimerManager.h"
#include "ImageManager.h"
#include "SceneManager.h"

#include "GameDataManager.h"
#include "CamerManager.h"
#include "ObjectRenderManager.h"
#include "InventoryManager.h"
#include "ItemManager.h"
#include "MapManager.h"
#include "UIManager.h"
#include "ShopManager.h"
#include "Input.h"

#define DELTA_TIME TimerManager::GetSingleton()->GetDeltaTime() 
#define GAMEDATA_MANAGER GameDataManager::GetSingleton()
#define GLOBAL_POS_X GameDataManager::GetSingleton()->GetGlobalPosX()
#define GLOBAL_POS_Y GameDataManager::GetSingleton()->GetGlobalPosY()
#define GLOBAL_POS CamerManager::GetSingleton()->GetGlobalPos()
#define RENDER_MANAGER ObjectRenderManager::GetSingleton()
#define MAP_MANAGER MapManager::GetSingleton()
#define MAP MapManager::GetSingleton()->GetMap()
#define INVEN_MANAGER InventoryManager::GetSingleton()
#define ITEM_MANAGER ItemManager::GetSingleton()
#define SHOP_MANAGER ShopManager::GetSingleton()
#define GET_KEY_DOWN(key) Input::GetButtonDown(key)
#define GET_KEY_UP(key) Input::GetButtonUp(key)
#define GET_KEY_STAY(key) Input::GetButton(key)
#define UI_MANAGER UIManager::GetSingleton()

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;
extern int windowX;
extern int windowY;