#include "MapManager.h"
#include "Image.h"
#include "OreObject.h"
#include "Interaction.h"

MapManager::MapManager() :
    mapInfo{}, selectDungeon{ nullptr }, ladderDownCheck{ false },  exit{}{}

void MapManager::Init()
{
}

void MapManager::DrawMapLayer(HDC hdc, int LayerNum)
{
    if (LayerNum == 1) LayerNum = 2;
    else if (LayerNum == 2) LayerNum = 1;
    else if (LayerNum == 3) LayerNum = 0;
    for (int y = 0; y < mapInfo.mapSizeY; ++y) {
        for (int x = 0; x < mapInfo.mapSizeX; ++x) {
            selectDungeon->Render(hdc,
                mapInfo.rect[y][x].left + (TILE_SIZE / 2) - GLOBAL_POS.x,
                mapInfo.rect[y][x].top + (TILE_SIZE / 2) - GLOBAL_POS.y,
                mapInfo.tileInfo[LayerNum][y][x].frameX,
                mapInfo.tileInfo[LayerNum][y][x].frameY);
        }
    }
}

void MapManager::CreateOreObject()
{
    int maxObject = 0;
    int minObject = 0;
    if (mapInfo.mapSizeY == 0)mapInfo.mapSizeY = 1;
    if (mapInfo.mapSizeX == 0)mapInfo.mapSizeX = 1;
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty)
            {
                ++maxObject;
            }
        }
    }
    //���� ��ȸ�ϸ鼭 ������Ʈ ������ ������ �ִ밹���� ����.

    maxObject /= 4;
    minObject = maxObject / 2;
    int objectCost = minObject + (rand() % (maxObject - minObject));
    // ���� �ʿ� ������ ������Ʈ�� ����� ������

    for (int count = 0; count < objectCost;)
    {
        int posX = rand() % mapInfo.mapSizeX;
        int posY = rand() % mapInfo.mapSizeY;

        if (mapInfo.tileState[posY][posX] == Tile_State::Empty && mapInfo.object[posY][posX] == nullptr)
        {   //  �ش� Ÿ���� ���������, ��ĭ�� ��ٸ��� ���� ��� ������Ʈ �߰�
            if (posY > 0 && mapInfo.tileState[posY - 1][posX] != Tile_State::LadderUp)
            {
                mapInfo.object[posY][posX] = new OreObject(mapInfo.dungeonTiles,posX, posY);
                ++count;
                if (rand() % (objectCost / 6) == 0)
                {   // ������ ���濡 ����Ͽ� Ż�ⱸ ����
                    POINT buffer;
                    buffer.x = posX;
                    buffer.y = posY;
                    exit.push_back(buffer);
                }
            }
        }
        if (count >= objectCost && exit.size() == 0)
        {   // ������ Ż�ⱸ�� ���ٸ� Ż�ⱸ ����
            POINT buffer;
            buffer.x = posX;
            buffer.y = posY;
            exit.push_back(buffer);
        }
    }
}

void MapManager::Update()
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty && mapInfo.object[y][x] != nullptr)
            {
                mapInfo.object[y][x]->Update();
            }
        }
    }
}

void MapManager::Release()
{
    Clear();
    ReleaseSingleton();
}

void MapManager::ClearObject()
{
    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Empty && mapInfo.object[y][x] != nullptr)
            {
                SAFE_RELEASE(mapInfo.object[y][x]);
            }
        }
    }
}

void MapManager::Clear()
{
    ClearObject();
    exit.clear();
    RENDER_MANAGER->VectorClear();
    ITEM_MANAGER->ItemClear();
}

void MapManager::DeleteMapObject(POINT pos)
{
    mapInfo.object[pos.y][pos.x] = nullptr;
    for (int i = 0; i < exit.size(); ++i)
    {
        if (exit[i].x == pos.x && exit[i].y == pos.y)
        {
            mapInfo.tileInfo[2][pos.y][pos.x].frameX = 13;
            mapInfo.tileInfo[2][pos.y][pos.x].frameY = 10;
            mapInfo.tileState[pos.y][pos.x] = Tile_State::LadderDown;
        }
    }
}

void MapManager::CreateObject(Interaction* object, POINT pos)
{
    mapInfo.object[pos.y][pos.x] = object;
}

void MapManager::Interactions(POINT pos)
{
    switch (mapInfo.tileState[pos.y][pos.x])
    {
    case Tile_State::LadderDown:
        Clear();
        GAMEDATA_MANAGER->SetMapNum(GAMEDATA_MANAGER->GetMapNum() + 1);
        SceneManager::GetSingleton()->ChangeScene("MineScene");
        break;
    case Tile_State::LadderUp:
        Clear();
        GAMEDATA_MANAGER->SetMapNum(0);
        SceneManager::GetSingleton()->ChangeScene("TopFloorScene");
        break;
    default:
        if(mapInfo.object[pos.y][pos.x] != nullptr)
        {

            mapInfo.object[pos.y][pos.x]->InteractionAction();
        }
        break;
    }
    cout << pos.y << pos.x << endl;
}

void MapManager::SetDungeonImage()
{
    if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Gray)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Gray.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice)
    {        
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Ice2)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Ice2.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Red)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Red.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Sand2)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Sand2.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Slime)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Slime.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Soil)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Soil.bmp", 256, 288, 16, 18);
    }
    else if (mapInfo.dungeonTiles == Dungeon_Tiles::Dungeon_Stone)
    {
        selectDungeon = ImageManager::GetSingleton()->FindImage("Image/Dungeon/Dungeon_Stone.bmp", 256, 288, 16, 18);
    }
}

void MapManager::Load(int num)
{
    HANDLE hFile = CreateFile(GAMEDATA_MANAGER->GetMapString().c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    DWORD readByte;
    if (ReadFile(
        hFile,
        &mapInfo,
        sizeof(MAP_INFO),
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }
    // �� �ε�

    SetDungeonImage();
    // �ش� �ʿ� �˸´� �̹��� ����

    CamerManager::GetSingleton()->SetMapSize(MAP->mapSizeX, MAP->mapSizeY);
    // �۷ι� ������ �� ũ�� ����

    CloseHandle(hFile);
}

void MapManager::DrawMapCollision(HDC hdc)
{

    for (int y = 0; y < mapInfo.mapSizeY; ++y)
    {
        for (int x = 0; x < mapInfo.mapSizeX; ++x)
        {
            if (mapInfo.tileState[y][x] == Tile_State::Wall || mapInfo.object[y][x] != nullptr)
            {
                if (mapInfo.tileState[y][x] == Tile_State::Wall)
                    pen = (HPEN)CreateSolidBrush(RGB(0, 128, 64));
                if (mapInfo.object[y][x] != nullptr)
                    pen = (HPEN)CreateSolidBrush(RGB(30, 30, 30));
                oPen = (HPEN)SelectObject(hdc, pen);
                Rectangle(hdc,
                    mapInfo.rect[y][x].left   - GLOBAL_POS.x,
                    mapInfo.rect[y][x].top     - GLOBAL_POS.y,
                    mapInfo.rect[y][x].right   - GLOBAL_POS.x,
                    mapInfo.rect[y][x].bottom - GLOBAL_POS.y);
                SelectObject(hdc, oPen);
                DeleteObject(pen);
            }
        }
    }
}
