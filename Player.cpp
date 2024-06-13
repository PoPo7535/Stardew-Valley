#pragma once

#include "Player.h""
#include "PlayerStatePick.h"
#include "PlayerStateMove.h"
#include "PlayerStateIdel.h"
#include "Image.h"
#include "Config.h"
#include "CommonFunction.h"

Player::Player() :
	playerStateMove{ nullptr },
	playerStatePick{ nullptr },
	playerDirection{ MoveDirection::Down },
	playerState{ PlayerState::Idle }
{}

HRESULT Player::Init()
{
	// 플레이어 스폰위치
	for (int y = 0; y < MAP->mapSizeY; ++y)
	{
		for (int x = 0; x < MAP->mapSizeX; ++x)
		{
			if (MAP_MANAGER->GetMap()->tileState[y][x] == Tile_State::LadderUp)
			{
				pos.x = (float)((x + 1) * TILE_SIZE - (TILE_SIZE / 2));
				pos.y = (float)((y + 1) * TILE_SIZE + (TILE_SIZE / 2));
				break;
			}
		}
	}

	// 플레이어 상태클래스 초가화
	playerStateMove = new PlayerStateMove(this);
	playerStateMove->Init();
	playerStatePick = new PlayerStatePick(this);
	playerStatePick->Init();
	playerStateIdel = new PlayerStateIdel(this);
	playerStateIdel->Init();



	//플레이어 기본정보
	
	moveSpeed = 70.0f;
	bodySize = 10;
	return S_OK;
}

void Player::Update()
{
	SetRect(&rect, pos, bodySize);
	switch (playerState) {
	case PlayerState::Idle:
		playerStateIdel->Update();
		KeyDownChangeState();
		break;
	case PlayerState::Move:
		playerStateMove->Update();
		KeyDownChangeState();
		break;
	case PlayerState::Pick:
		playerStatePick->Update();
		break;
	}

	CamerManager::GetSingleton()->SetGlobalPos(pos);
	GAMEDATA_MANAGER->SetPlayerPos(pos);
}

void Player::Render(HDC hdc)
{
	switch (playerState) {
	case PlayerState::Idle:
		playerStateIdel->Render(hdc);
		break;
	case PlayerState::Pick:
		playerStatePick->Render(hdc);
		break;
	case PlayerState::Move:
		playerStateMove->Render(hdc);
		break;
	}
}

void Player::Release()
{
	SAFE_RELEASE(playerStatePick);
	SAFE_RELEASE(playerStateMove);
	SAFE_RELEASE(playerStateIdel);
}

const POINT Player::GetFrontTilePos() const
{
	POINT result = GetPosTile(pos);
	switch (playerDirection)
	{
	case MoveDirection::Up:
		if (result.y != 0)
		{
			result.y -= 1;
		}
		break;
	case MoveDirection::Down:
		if (result.y != MAP->mapSizeY) 
		{
			result.y += 1;
		}
		break;
	case MoveDirection::Left:
		if (result.x != 0) 
		{
			result.x -= 1;
		}
		break;
	case MoveDirection::Right:
		if (result.x != MAP->mapSizeX) 
		{
			result.x += 1;
		}
		break;
	}
	return result;
}

void Player::KeyDownChangeState()
{
	if (GET_KEY_STAY(VK_UP) || GET_KEY_STAY(VK_DOWN) || GET_KEY_STAY(VK_LEFT) || GET_KEY_STAY(VK_RIGHT))
	{
		playerState = PlayerState::Move;
	}
	if (GET_KEY_STAY('C'))
	{
		int itemCode = INVEN_MANAGER->GetInventoryInfo(UI_MANAGER->GetSelectItemNum(),0)->itemCode;
		if (TOOL_ITEM(itemCode))
		{
			playerState = PlayerState::Pick;
		}
	}
	else if (GET_KEY_DOWN('X'))
	{
		POINT result = GetFrontTilePos();
		MAP_MANAGER->Interactions(result);
	}

	// 인벤토리에서 플레이어가 들 아이템을 선택
	static const int key[12] = { '1','2','3','4','5','6','7','8','9','0',VK_OEM_MINUS,VK_OEM_PLUS };
	for (int input = 0; input < 12; ++input)
	{
		if (GET_KEY_DOWN(key[input]))
		{
			UI_MANAGER->SetSelectItemNum(input);
		}
	}
}