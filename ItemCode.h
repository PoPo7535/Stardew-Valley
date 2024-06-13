#pragma once
#include <string>
#define RESOURCE_ITEM(num) (1 <= num && num <= 12 )
#define TOOL_ITEM(num) (13 <= num && num <= 17)

#define STONE 1
#define COAL 2
#define COPPER 3
#define STEEL 4
#define GOLD 5
#define IRIDIUM 6

#define EMERALD 7
#define TOPAZ 8
#define AQUAMARINE 9
#define RUBY 10
#define AMETHYST 11
#define DIAMOND 12

#define STEEL_SHORT_SWORD 13
#define NORMAL_PICK 14
#define COPPER_PICK 15
#define IRON_PICK 16
#define GOLD_PICK 17

using namespace std;

// 도구아이템
struct ToolItemInfo
{
	ToolItemInfo()
		: maxDamage{ 0 }, minDamage{ 0 }, gold{ 0 }, info{ "" }, name{""}{}
	int maxDamage;
	int minDamage;
	int gold;
	string name;
	string info;
};

// 자원아이템
struct ResourceItemInfo
{
	ResourceItemInfo()
		:gold{ 0 }, info{ "" }, name{ "" }{}
	int gold;
	string name;
	string info;
};

