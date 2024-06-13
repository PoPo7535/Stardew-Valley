#pragma once
#include"Config.h"
class Image;
class ItemsToSell;
struct ShopImage
{
	Image* main;
	POINTFLOAT mainPos;
	RECT mainRect;

	Image* up;
	POINTFLOAT upPos;
	RECT upRect;

	Image* down;
	POINTFLOAT downPos;
	RECT downRect;

	Image* cancel;
	POINTFLOAT cancelPos;
	RECT cancelRect;
};
struct Store
{
	Image* portrait;
	POINTFLOAT portraitPos;
	string masterName;
	int* salesList;
	int salesListMaxNum;
};
enum class ShopType
{
	BlackSmith , None
};
class ShopManager : public Singleton<ShopManager>
{
private:
	friend class ItemsToSell;
	ItemsToSell* itemToSell;

	ShopImage shopImage;
	ShopType shopType;
	Store blackSmith;
	Image* coinImage;
	bool isActive;
	int salesListStartNum;
public:
	void ActiveShop(string shopTypeString);
	ShopManager();
	void Init();
	bool Update();
	void Render(HDC hdc);
	POINT GetInventoryNum();
	int GetShopSoldNum();
	void Release();
};

