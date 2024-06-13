#include "PlayerStateMove.h"
#include "Image.h"
#include "Config.h"
#include "Player.h"
#include "CommonFunction.h"

void PlayerStateMove::Move(float posX, float posY)
{
	// �÷��̾� �浹üũ�� RECT ����
	RECT rectTemp;
	SetRect(&rectTemp, POINTFLOAT{ posX,posY }, player->bodySize);

	// �ڱ� pos���� ��������, ���° Ÿ������ Ȯ���ϴ� �Լ�
	POINT playerPos = GetPosTile(player->pos);
	for (int y = playerPos.y - 2; y < playerPos.y + 2; ++y)
	{
		for (int x = playerPos.x - 2; x < playerPos.x + 2; ++x)
		{
			if (MAP->tileState[y][x] != Tile_State::Empty)
			{	// �ش� Ÿ���� ����ִ� ������ �ƴ϶�� �浹�˻�
				RECT rc;
				if (IntersectRect(&rc, &rectTemp, &MAP->rect[y][x]))
				{
					return;
				}
			}
			if (MAP->object[y][x] != nullptr)
			{	// �ش� Ÿ�Ͽ� ������Ʈ�� �ִٸ� �浹�˻�
				RECT rc;
				RECT temp = MAP->object[y][x]->GetRect();
				if (IntersectRect(&rc, &rectTemp, &temp))
				{
					return;
				}
			}
		}
	}
	// �浹�� ������ �ʾҴٸ� �̵�
	player->SetPos(POINTFLOAT{ posX ,posY });
}

void PlayerStateMove::MovePlayer()
{
	if (GET_KEY_STAY(VK_UP))
	{
		Move(player->pos.x, player->pos.y - (player->moveSpeed * DELTA_TIME));
		player->playerDirection = MoveDirection::Up;
	}
	else if (GET_KEY_STAY(VK_DOWN))
	{
		Move(player->pos.x, player->pos.y + (player->moveSpeed * DELTA_TIME));
		player->playerDirection = MoveDirection::Down;
	}
	if (GET_KEY_STAY(VK_LEFT))
	{
		Move(player->pos.x - (player->moveSpeed * DELTA_TIME), player->pos.y);
		player->playerDirection = MoveDirection::Left;
	}
	else if (GET_KEY_STAY(VK_RIGHT))
	{
		Move(player->pos.x + (player->moveSpeed * DELTA_TIME), player->pos.y);
		player->playerDirection = MoveDirection::Right;
	}
}

HRESULT PlayerStateMove::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Player/Player_Move.bmp", 128, 128, 8, 4);
	return S_OK;
}

void PlayerStateMove::Update()
{
	frameTime += DELTA_TIME;
	if (frameTime > 0.1f)
	{
		frameTime -= 0.1f;
		++frame;
	}
	MovePlayer();
	CheckAction();
}
void PlayerStateMove::Render(HDC hdc)
{
	if (player->playerDirection == MoveDirection::Up || player->playerDirection == MoveDirection::Down)
	{
		img->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y,
			frame % 8,
			player->playerDirection);
	}
	else if (player->playerDirection == MoveDirection::Left || player->playerDirection == MoveDirection::Right)
	{
		img->Render(hdc,
			player->pos.x - GLOBAL_POS.x,
			player->pos.y - player->bodySize - GLOBAL_POS.y,
			frame % 6,
			player->playerDirection);
	}
}

void PlayerStateMove::Release() {}

bool PlayerStateMove::CheckAction()
{
	if (GET_KEY_STAY(VK_UP) || GET_KEY_STAY(VK_DOWN) || GET_KEY_STAY(VK_LEFT) || GET_KEY_STAY(VK_RIGHT))
	{
		return false;
	}
	else
	{
		frame = 0;
		frameTime = 0.0f;
		player->playerState = PlayerState::Idle;
	}
	return false;
}

PlayerStateMove::PlayerStateMove(Player* player)
	:player{ player }, img{ nullptr }, frameTime{ 0.0f }, frame{ 0 }{};