#pragma once
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	POINTFLOAT playerPos;
	const string mapName[5];
	int mapNum;
	int playerMoney;
public:
	GameDataManager() :
		playerPos{}, 
		mapNum{ 0 }, 
		playerMoney{ 0 },
		mapName
	{
		"Save/SaveMapData_Main.map",
		"Save/SaveMapData_Soil.map",
		"Save/SaveMapData_Ice.map",
		"Save/SaveMapData_Red.map",
		"Save/SaveMapData_End.map"
	} {};
	void Init() {}
public:

	void SetPlayerPos(POINTFLOAT pos) { playerPos = pos; }
	POINTFLOAT GetPlayerPos() { return playerPos; }

	int GetPlayerMoney() { return playerMoney; }
	void SetPlayerMoney(int newMoney) { playerMoney = newMoney; }
	void AddPlayerMoney(int addMoney) { playerMoney += addMoney; }

	void SetMapNum(int num) { mapNum = num; }
	int GetMapNum() { return mapNum; }
	const string GetMapString() const { return mapName[mapNum]; }



	void Release() { this->ReleaseSingleton(); }
};