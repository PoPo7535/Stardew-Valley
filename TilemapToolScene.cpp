#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Config.h"
HRESULT TilemapToolScene::Init()
{
    SetWindowSize(20, 10, TILEMAPTOOL_SIZE_X*3, TILEMAPTOOL_SIZE_Y*3);
     windowX = TILEMAPTOOL_SIZE_X;
    windowY = TILEMAPTOOL_SIZE_Y;
    {
        mineImage[0] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Gray.bmp", 256, 288, 16, 18);
        mineImage[1] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice.bmp", 256, 288, 16, 18);
        mineImage[2] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice2.bmp", 256, 288, 16, 18);
        mineImage[3] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Red.bmp", 256, 288, 16, 18);
        mineImage[4] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand.bmp", 256, 288, 16, 18);
        mineImage[5] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand2.bmp", 256, 288, 16, 18);
        mineImage[6] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Slime.bmp", 256, 288, 16, 18);
        mineImage[7] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
        mineImage[8] = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone.bmp", 256, 288, 16, 18);
        layer.numImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_Layer.bmp", 64, 64, 4, 1);
        layer.modeImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_LayerMode.bmp", 64, 64, 4, 1);
        tileStateImage = ImageManager::GetSingleton()->FindImage("Image/Dungeon/TileMapTool_TileState.bmp", 80, 80, 5, 1);
    }
    selectMineImage = mineImage[7];
    // ���� ��� ���� ���� �ʱ�ȭ
    for (int y = 0; y < 256; ++y)  // y��
    {
        for (int x = 0; x < 256; ++x)  // x�� 
        {
            SetRect(&(mapInfo.rect[y][x]),
                x * (TILE_SIZE),
                y * (TILE_SIZE),
                x * (TILE_SIZE) + (TILE_SIZE),
                y * (TILE_SIZE) + (TILE_SIZE));
            mapInfo.tileState[y][x] = tileState;
            mapInfo.tileInfo[0][y][x].frameX = 0;
            mapInfo.tileInfo[0][y][x].frameY = 1;
            mapInfo.tileInfo[1][y][x].frameX = 0;
            mapInfo.tileInfo[1][y][x].frameY = 1;
            mapInfo.tileInfo[2][y][x].frameX = 0;
            mapInfo.tileInfo[2][y][x].frameY = 1;
        }
    }

    // ���õ� Ÿ��
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;
    return S_OK;
}

void TilemapToolScene::Update()
{
    mouse = g_ptMouse;
    RECT rect;
    GetClientRect(g_hWnd, &rect);
    POINT view;
    view.x = rect.right - rect.left;
    view.y = rect.bottom - rect.top;
    if (view.x != TILEMAPTOOL_SIZE_X || view.y != TILEMAPTOOL_SIZE_Y) 
    {
        view.x /= TILEMAPTOOL_SIZE_X;
        view.y /= TILEMAPTOOL_SIZE_Y;
        mouse.x /= view.x;
        mouse.y /= view.y;
    }

    
    // Ÿ�ϸ��� ���Ű
    {
        if (GET_KEY_DOWN('1'))             //==========================
            layer.num = 0;                                               //
        else if (GET_KEY_DOWN('2'))        //
            layer.num = 1;                                               //  ���̾� ����
        else if (GET_KEY_DOWN('3'))        //
            layer.num = 2;                                               //
        else if (GET_KEY_DOWN('4'))        //
            layer.num = 3;                                               //
        if (GET_KEY_DOWN('Z'))             //==========================
        {                                                               //
            if (tileState == Tile_State::Empty)                         //
                tileState = Tile_State::LadderDown;                     //
            else if (tileState == Tile_State::LadderDown)               //
                tileState = Tile_State::LadderUp;                       //
            else if (tileState == Tile_State::LadderUp)                 // Ÿ�� ���� ����
                tileState = Tile_State::Light;                          //
            else if (tileState == Tile_State::Light)                    //
                tileState = Tile_State::Wall;                           //
            else if (tileState == Tile_State::Wall)                     //
                tileState = Tile_State::Empty;                          //
        }                                                               //
        else if (GET_KEY_DOWN(VK_UP))      //==========================
        {                                                               //
            --mapPosY;                                                  //
            if (mapPosY < 0) mapPosY = 0;                               //
        }                                                               //
        else if (GET_KEY_DOWN(VK_DOWN))    //
        {                                                               //
            ++mapPosY;                                                  //
        }                                                               //
        else if (GET_KEY_DOWN(VK_RIGHT))   // �������� ��ũ�� ����
        {                                                               //
            ++mapPosX;                                                  //
        }                                                               //
        else if (GET_KEY_DOWN(VK_LEFT))    //
        {                                                               //
            --mapPosX;                                                  //
            if (mapPosX < 0) mapPosX = 0;                               //
        }                                                               //==========================
        else if (GET_KEY_DOWN(VK_NUMPAD6)) //
        {                                                               //
            ++mapInfo.mapSizeX;                                         // 
        }                                                               //
        else if (GET_KEY_DOWN(VK_NUMPAD4)) // 
        {                                                               //
            --mapInfo.mapSizeX;                                         //
        }                                                               //
        else if (GET_KEY_DOWN(VK_NUMPAD8)) // 
        {                                                               //
            --mapInfo.mapSizeY;                                         // ���� ��ũ�� ����
        }                                                               //
        else if (GET_KEY_DOWN(VK_NUMPAD5)) // 
        {                                                               //
            ++mapInfo.mapSizeY;                                         // 
        }                                                               //==========================
        else if (GET_KEY_DOWN(VK_NUMPAD3)) //
        {                                                               //
            if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)    //
            {                                                           //
                selectMineImage = mineImage[1];                             //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Ice;      //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)//
            {                                                           //
                selectMineImage = mineImage[2];                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Ice2;     //  ���ÿ��� ����
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
            {                                                           //
                selectMineImage = mineImage[3];                             //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Red;      //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)//
            {                                                           //
                selectMineImage = mineImage[4];                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Sand;     //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)//
            {                                                           //
                selectMineImage = mineImage[5];                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Sand2;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
            {                                                           //
                selectMineImage = mineImage[6];                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Slime;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
            {                                                           //
                selectMineImage = mineImage[7];                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Soil;     //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
            {                                                           //
                selectMineImage = mineImage[8];                           //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Stone;    //
            }                                                           //
            else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
            {                                                           //
                selectMineImage = mineImage[0];                            //
                mapInfo.dungeonTiles = Dungeon_Tiles::Dungeon_Gray;     //=========================
            }                                                           //
        }                                                               //
        else if (GET_KEY_DOWN(VK_NUMPAD1)) //
        {                                                               //
            mapInfoTemp = mapInfo;                                      //
            for (int y = 0; y < mapInfo.mapSizeY; ++y)                  //  ���̾� 1ĭ�� �б�
            {                                                           //
                for (int x = 0; x < mapInfo.mapSizeX; ++x)              //
                {                                                       //
                    mapInfo.tileInfo[1][y][x].frameX = mapInfoTemp.tileInfo[0][y][x].frameX;
                    mapInfo.tileInfo[1][y][x].frameY = mapInfoTemp.tileInfo[0][y][x].frameY;
                    mapInfo.tileInfo[2][y][x].frameX = mapInfoTemp.tileInfo[1][y][x].frameX;
                    mapInfo.tileInfo[2][y][x].frameY = mapInfoTemp.tileInfo[1][y][x].frameY;
                    mapInfo.tileInfo[0][y][x].frameX = mapInfoTemp.tileInfo[2][y][x].frameX;
                    mapInfo.tileInfo[0][y][x].frameY = mapInfoTemp.tileInfo[2][y][x].frameY;
                    mapInfo.tileInfo[1][y][x].frameX = mapInfoTemp.tileInfo[0][y][x].frameX;
                }
            }
        }
        else if (GET_KEY_DOWN(VK_NUMPAD2))
        {
            ++layer.mode;
            if (layer.mode == 4) layer.mode = 0;
        }

        mapPrintX = mapPosX + 20;
        if (mapInfo.mapSizeX < mapPrintX)
            mapPrintX = mapInfo.mapSizeX;
        mapPrintY = mapPosY + 20;
        if (mapInfo.mapSizeY < mapPrintY)
            mapPrintY = mapInfo.mapSizeY;
    }
    
    // ������ ��� ���� ���� �ʱ�ȭ
    for (int y = 0; y < 18; ++y)    // y��
    {
        for (int x = 0; x < 16; ++x)    // x��
        {
            SetRect(&(sampleTileInfo[y][x].rc),
                TILEMAPTOOL_SIZE_X - selectMineImage->GetWidth() + x * TILE_SIZE,
                y * TILE_SIZE,
                TILEMAPTOOL_SIZE_X - selectMineImage->GetWidth() + x * TILE_SIZE + TILE_SIZE,
                y * TILE_SIZE + TILE_SIZE);

            sampleTileInfo[y][x].frameX = x;
            sampleTileInfo[y][x].frameY = y;
        }
    }
    // ���ÿ������� ������ ����
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - selectMineImage->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = selectMineImage->GetHeight();

    if (PtInRect(&(sampleArea), mouse))
    {
        if (GET_KEY_DOWN(VK_LBUTTON)) {
            int posX = mouse.x - sampleArea.left;
            selectedSampleTile.frameX = sampleTileWidth = posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            selectedSampleTile.frameY = sampleTileHeight = posY / TILE_SIZE;
        }

        if (GET_KEY_UP(VK_LBUTTON)) {
            int posX = mouse.x - sampleArea.left;
            sampleTileWidth -= posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            sampleTileHeight -= posY / TILE_SIZE;

            if (sampleTileWidth < 0) sampleTileWidth *= -1;
            if (sampleTileHeight < 0) sampleTileHeight *= -1;
        }
    }

    // ���ο������� ���õ� ���� ������ ����
    if (layer.num != 3)
    {
        for (int y = mapPosY; y < mapPosY + 20; ++y) {
            for (int x = mapPosX; x < mapPosX + 20; ++x) {
                RECT rc = mapInfo.rect[y][x];
                rc.left -= (mapPosX * TILE_SIZE); rc.right -= (mapPosX * TILE_SIZE);
                rc.top -= (mapPosY * TILE_SIZE); rc.bottom -= (mapPosY * TILE_SIZE);
                if (PtInRect(&rc, mouse)) {
                    if (GET_KEY_STAY(VK_LBUTTON)) {
                        for (int height = 0; height <= sampleTileHeight; ++height)
                        {
                            if (mapPosY + height >= mapPrintY) break;
                            for (int width = 0; width <= sampleTileWidth; ++width)
                            {
                                if (mapPosX + height >= mapPrintX) break;
                                mapInfo.tileInfo[layer.num][y + height][x + width].frameX = selectedSampleTile.frameX + width;
                                mapInfo.tileInfo[layer.num][y + height][x + width].frameY = selectedSampleTile.frameY + height;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int y = mapPosY; y < mapPosY + 20; ++y) {
            for (int x = mapPosX; x < mapPosX + 20; ++x) {
                RECT rc = mapInfo.rect[y][x];
                rc.left -= (mapPosX * TILE_SIZE); rc.right -= (mapPosX * TILE_SIZE);
                rc.top -= (mapPosY * TILE_SIZE); rc.bottom -= (mapPosY * TILE_SIZE);
                if (PtInRect(&rc, mouse)) {
                    if (GET_KEY_STAY(VK_LBUTTON)) {
                        mapInfo.tileState[y][x] = tileState;
                    }
                }
            }
        }
    }

    // ���̺�
    if (GET_KEY_UP(VK_NUMPAD7))
        Save();
    // �ε�
    if (GET_KEY_UP(VK_NUMPAD9))
        Load();

    backUpTime += DELTA_TIME;
    if (backUpTime >= 300.0f)
    {
        BackUpSave();
    }
}

void TilemapToolScene::Render(HDC hdc)
{
    // ���� ����
    if (layer.mode == 0) // ���̾� ��尡 ǥ�ػ����϶�
    {
        for (int z = 2; z > -1; --z) {
            for (int y = mapPosY; y < mapPrintY; ++y) {
                for (int x = mapPosX; x < mapPrintX; ++x) {
                    selectMineImage->Render(hdc,
                        mapInfo.rect[y][x].left + (TILE_SIZE / 2) - (mapPosX * TILE_SIZE),
                        mapInfo.rect[y][x].top + (TILE_SIZE / 2) - (mapPosY * TILE_SIZE),
                        mapInfo.tileInfo[z][y][x].frameX,
                        mapInfo.tileInfo[z][y][x].frameY);
                }
            }
        }
    }
    else // ���̾� ��尡 �� �ش� ���̾ ����ϰ� ���� ����
    {
        for (int y = mapPosY; y < mapPrintY; ++y) {
            for (int x = mapPosX; x < mapPrintX; ++x) {
                selectMineImage->Render(hdc,
                    mapInfo.rect[y][x].left + (TILE_SIZE / 2) - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].top + (TILE_SIZE / 2) - (mapPosY * TILE_SIZE),
                    mapInfo.tileInfo[layer.mode - 1][y][x].frameX,
                    mapInfo.tileInfo[layer.mode - 1][y][x].frameY);
            }
        }
    }

    if (layer.num == 3)
    {
        for (int y = mapPosY; y < mapPrintY; ++y) {
            for (int x = mapPosX; x < mapPrintX; ++x) {
                if (mapInfo.tileState[y][x] == Tile_State::Empty)
                    pen = (HPEN)CreateSolidBrush(RGB(20, 20, 20));
                if (mapInfo.tileState[y][x] == Tile_State::Light)
                    pen = (HPEN)CreateSolidBrush(RGB(239, 228, 176));
                if (mapInfo.tileState[y][x] == Tile_State::LadderDown)
                    pen = (HPEN)CreateSolidBrush(RGB(128, 64, 0));
                if (mapInfo.tileState[y][x] == Tile_State::LadderUp)
                    pen = (HPEN)CreateSolidBrush(RGB(255, 128, 64));
                if (mapInfo.tileState[y][x] == Tile_State::Wall)
                    pen = (HPEN)CreateSolidBrush(RGB(0, 128, 64));
                oPen = (HPEN)SelectObject(hdc, pen);
                Rectangle(hdc,
                    mapInfo.rect[y][x].left - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].top - (mapPosY * TILE_SIZE),
                    mapInfo.rect[y][x].right - (mapPosX * TILE_SIZE),
                    mapInfo.rect[y][x].bottom - (mapPosY * TILE_SIZE));
                SelectObject(hdc, oPen);
                DeleteObject(pen);
            }
        }
    }

    // ���̾� ����
    layer.numImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 150, layer.num, 0);
    if (layer.mode == 0)
        layer.modeImage->Render(hdc, TILEMAPTOOL_SIZE_X - 281, TILEMAPTOOL_SIZE_Y - 150, 3, 0);
    else
        layer.modeImage->Render(hdc, TILEMAPTOOL_SIZE_X - 281, TILEMAPTOOL_SIZE_Y - 150, layer.mode - 1, 0);
    if (tileState == Tile_State::Empty)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 0, 0);
    else if (tileState == Tile_State::LadderDown)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 1, 0);
    else if (tileState == Tile_State::LadderUp)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 2, 0);
    else if (tileState == Tile_State::Light)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 3, 0);
    else if (tileState == Tile_State::Wall)
        tileStateImage->Render(hdc, TILEMAPTOOL_SIZE_X - 265, TILEMAPTOOL_SIZE_Y - 222, 4, 0);


    // ���õ� Ÿ��
    selectMineImage->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - 265,
        TILEMAPTOOL_SIZE_Y - 100,
        selectedSampleTile.frameX,
        selectedSampleTile.frameY,
        0,
        0);

    // ������� ���� ����
    selectMineImage->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - selectMineImage->GetWidth(),
        0);
}

void TilemapToolScene::Release()
{
}

TilemapToolScene::TilemapToolScene() :
    pen{},
    oPen{},
    sampleTileInfo{},
    selectedSampleTile{},
    sampleTileWidth{ NULL }, sampleTileHeight{ NULL },
    mineImage{},
    layer{},
    mouse{},
    mapInfo{},
    mapPrintX{ 20 }, mapPrintY{ 20 },
    mapPosX{ 0 }, mapPosY{ 0 },
    backUpNum{ 0 }, backUpTime{ 0 },
    tileState{ Tile_State::Empty }
{}

void TilemapToolScene::Save()
{
    int saveIndex;
    cout << "���̺��� ���� ��ȣ�� �Է��Ͽ� �ֽʽÿ�. : ";
    cin >> saveIndex;
    string saveFileName = "Save/saveMapData_" + to_string(saveIndex);
    saveFileName += ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // �б�, ����
        0, NULL,                // ����, ���� ���
        CREATE_ALWAYS,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // ����
    DWORD byteSize = sizeof(MAP_INFO);
    //mapInfo2.dungeonTiles = mapInfo.dungeonTiles;
    //mapInfo2.mapSizeX = mapInfo.mapSizeX;
    //mapInfo2.mapSizeY = mapInfo.mapSizeY;
    //mapInfo2.dungeonTiles = mapInfo.dungeonTiles;
    //for (int z = 0; z < 3; ++z) {
    //    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
    //        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
    //            mapInfo2.rect[y][x] = mapInfo.rect[y][x];
    //            mapInfo2.tileInfo[z][y][x] = mapInfo.tileInfo[z][y][x];
    //            mapInfo2.tileState[y][x] = mapInfo.tileState[y][x];
    //        }
    //    }
    //}
    DWORD writtenByte;
    if (WriteFile(hFile,                            // ���� �ڵ�
        &mapInfo,                                   // �޸� �����ּ�
        sizeof(MAP_INFO),                           // �޸� ũ��
        &writtenByte,                               // ���� ������ ���� �뷮
        NULL) == false)                             // ???
    {
        cout << "���� ���� \n";
    }
    CloseHandle(hFile);
}

void TilemapToolScene::BackUpSave()
{
    string saveFileName = "Save/Back/BackUpMapData_" + to_string(backUpNum) + ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // �б�, ����
        0, NULL,                // ����, ���� ���
        CREATE_ALWAYS,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);
    // ����

    DWORD byteSize = sizeof(MAP_INFO);
    DWORD writtenByte;
    if (WriteFile(hFile,                            // ���� �ڵ�
        &mapInfo,                                   // �޸� �����ּ�
        sizeof(MAP_INFO),                           // �޸� ũ��
        &writtenByte,                               // ���� ������ ���� �뷮
        NULL) == false)                             // ???
        cout << "���� ���� \n";
    else
    {
        cout << backUpNum++ << "�� ����Ϸ�.\n";
        backUpTime = 0;
    }
    if (backUpNum >= 100) backUpNum = 0;
    CloseHandle(hFile);
}

void TilemapToolScene::Load()
{
    int loadIndex;
    cout << "�ε��� ���� ��ȣ�� �Է��Ͽ� �ֽʽÿ�. : ";
    cin >> loadIndex;
    string loadFileName = "Save/SaveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);
    //LPCVOID;
    
    // �б�
    DWORD readByte;
    if (ReadFile(
        hFile, 
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}
