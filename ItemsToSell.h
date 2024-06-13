#pragma once
#include "Config.h"

#define BAG 0
#define BAG_BUY_MONEY 300
class Image;
class ItemsToSell
{
private:
	ShopManager* shopManager;
	Image* salesListBag;
public:
	ItemsToSell(ShopManager* shopManager) 
		: shopManager{nullptr}, salesListBag{nullptr}
	{
		this->shopManager = shopManager;
	}
	void Init();
	void BuyItem();
	void SellItem();
	void Release();
	void RenderSaleslist(HDC hdc);
	
};

