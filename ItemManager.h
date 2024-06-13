#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemCode.h"
#include <unordered_map>

class Image;
class ItemManager : public Singleton<ItemManager>
{
private:
	unordered_map<int, ToolItemInfo> toolItmeInfo;
	unordered_map<int, ResourceItemInfo> resourceItemInfo;
	queue<Item*> itemQueue;
	vector<Item*> itemVector;
	Image* itemImage;
public:
	ItemManager();
	void Init();
	void Update();
	void Release();
public:
	const ToolItemInfo* GetToolItem(int key) const { return &toolItmeInfo.at(key); }
	const ResourceItemInfo* GetResourceItem(int key) { return &resourceItemInfo.at(key); }
	void CreateItem(int key, POINTFLOAT pos, int num = 1);

	void DeleteObjectVector();
	void DeleteObject(Item* obj);
	void ItemClear();
	void ItemRender(HDC hdc, int itemCode, int posX, int posY);
};
