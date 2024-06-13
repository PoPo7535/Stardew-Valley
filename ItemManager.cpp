#include "ItemManager.h"
#include "Image.h"
#include <fstream>
#include <locale>
#define AtlasSize 12

ItemManager::ItemManager() :toolItmeInfo{}, resourceItemInfo{}, itemVector{}, itemImage{nullptr}
{}
void ItemManager::Init()
{
	itemImage = ImageManager::GetSingleton()->FindImage("Image/item/Item.bmp", 192, 32, 12, 2);
	ResourceItemInfo resource;
	ToolItemInfo tool;
	string str = "";

	// 자원 아이템 초기화
	fstream resourcefile("ItemInfo/ResourceItemInfo.txt");
	while (getline(resourcefile, str))
	{
		int itemCode = stoi(str);
		getline(resourcefile, str);
		resource.gold = stoi(str);
		getline(resourcefile, str);
		resource.name = str;
		getline(resourcefile, str);
		resource.info = str;
		resourceItemInfo.insert(make_pair(itemCode, resource));
	}

	// 도구아이템 초기화
	fstream toolfile("ItemInfo/ToolItemInfo.txt");
	while (getline(toolfile, str))
	{
		int itemCode = stoi(str);
		getline(toolfile, str);
		tool.gold = stoi(str);
		getline(toolfile, str);
		tool.minDamage = stoi(str);
		getline(toolfile, str);
		tool.maxDamage = stoi(str);
		getline(toolfile, str);
		tool.gold = stoi(str);
		getline(toolfile, str);
		tool.name = str;
		getline(toolfile, str);
		tool.info = str;
		toolItmeInfo.insert(make_pair(itemCode, tool));
	}
}

void ItemManager::Update()
{
	DeleteObjectVector();
	for (int i = 0; i < itemVector.size(); ++i)
	{
		itemVector[i]->Update();
	}
}

void ItemManager::Release()
{
	toolItmeInfo.clear();
	resourceItemInfo.clear();
	ItemClear();
	ReleaseSingleton();
}

void ItemManager::CreateItem(int key, POINTFLOAT pos, int num)
{
	itemVector.push_back(new Item(key, pos, num));
}

void ItemManager::DeleteObjectVector()
{
	while (itemQueue.empty() == false)
	{
		for (vector<Item*>::iterator iter = itemVector.begin();
			iter != itemVector.end(); ++iter)
		{	// 백터를 순회하며 삭제
			if ((*iter) == itemQueue.front())
			{
				SAFE_RELEASE((*iter));
				itemVector.erase(iter);
				itemQueue.pop();
				break;
			}
		}
	}
}

void ItemManager::DeleteObject(Item* obj)
{
	itemQueue.push(obj);
}

void ItemManager::ItemClear()
{
	for (vector<Item*>::iterator iter = itemVector.begin();
		iter != itemVector.end(); ++iter)
	{	// 백터를 순회하며 삭제
		SAFE_RELEASE((*iter));
	}
	itemVector.clear();
	while (itemQueue.empty() == false)
	{
		itemQueue.pop();
	}
}

/// <summary> 입력된 아이템 코드 이미지를 출력한다. </summary>
void ItemManager::ItemRender(HDC hdc, int itemCode, int posX, int posY)
{
	POINT frame{ ((LONG)(itemCode - 1)) % AtlasSize ,(LONG)((itemCode - 1) / AtlasSize) };
	itemImage->Render(hdc, posX, posY, frame.x, frame.y);
}
