#pragma once
#include "ItemCode.h"
#include "Image.h"
class InventoryItem
{
private:
	ItemType itemType;
	ToolItemInfo* toolItemInfo;
	ResourceItemInfo* resourceItemInfo;
	Image* img;
	int itemCode;
public:
	InventoryItem() :itemType{ ItemType::Empty }, toolItemInfo{}, resourceItemInfo{}, itemCode{ 0 } ,img{ nullptr }{}

	void Release()
	{
		itemType = ItemType::Empty;
		itemCode = 0;
		toolItemInfo = nullptr;
		resourceItemInfo = nullptr;
		img = nullptr;
	};

	ToolItemInfo GetToolItemInfo() { return *toolItemInfo; }
	ResourceItemInfo GetResourceItemInfo() { return *resourceItemInfo; }

	void SetToolItemInfo(ToolItemInfo item) { toolItemInfo = &item; }
	void SetResourceItemInfo(ResourceItemInfo item) { resourceItemInfo = &item; }

	int GetItemCode() { return itemCode; }
	void SetItemCode(int itemCode) { this->itemCode = itemCode; }

	ItemType GetItemType() { return itemType; }
	void  SetItemType(ItemType itemType) { this->itemType = itemType; }
};

