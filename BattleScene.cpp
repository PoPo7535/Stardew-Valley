#include "BattleScene.h"
#include "CommonFunction.h"
#include "Image.h"
HRESULT BattleScene::Init()
{
    Load();
    {
        if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Gray.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice2.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Red.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand2.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Slime.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp");
        }
        else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
        {
            ImageManager::GetSingleton()->AddImage
            ("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18, true, RGB(255, 0, 255));
            selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone.bmp");
        }
    }

        ; // 26
    mapInfo.mapSizeY; // 15
    SetWindowSize(20, 10, 420 * 3, 240 * 3);
    windowX = 420;
    windowY = 240;
    return S_OK;
}

void BattleScene::Update()
{
    //420 240
}

void BattleScene::Render(HDC hdc)
{
    for (int z = 2; z > -1; --z) {
        for (int y = mapPosY; y < mapPrintY; ++y) {
            for (int x = mapPosX; x < mapPrintX; ++x) {
                selectDungeon->Render(hdc,
                    mapInfo.rect[y][x].left + (TILE_SIZE / 2) - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].top + (TILE_SIZE / 2) - (mapPosY * TILE_SIZE),
                    mapInfo.tileInfo[z][y][x].frameX,
                    mapInfo.tileInfo[z][y][x].frameY);
            }
        }
    }
}

void BattleScene::Release()
{

}

int BattleScene::Load(int num)
{
    int loadIndex;
    //cout << "로드할 맵의 번호를 입력하여 주십시오. : ";
    //cin >> loadIndex;
    string loadFileName = "Save/SaveMapData_" + to_string(num);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);
    //LPCVOID;

    // 읽기
    DWORD readByte;
    if (ReadFile(
        hFile,
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
    return 1;
}
