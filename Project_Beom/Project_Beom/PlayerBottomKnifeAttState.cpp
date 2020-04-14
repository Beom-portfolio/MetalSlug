#include "pch.h"
#include "PlayerBottomKnifeAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomStandState.h"
#include "GameObject.h"

PlayerBottomKnifeAttState::PlayerBottomKnifeAttState()
{
}

PlayerBottomKnifeAttState::~PlayerBottomKnifeAttState()
{
}

void PlayerBottomKnifeAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		if (0 == rand() % 2)
		{
			info.key = L"bottom_knife_att_r1";
			info.MaxFrame = 6;
		}
		else
		{
			info.key = L"bottom_knife_att_r2";
			info.MaxFrame = 4;
		}
	}
	else
	{
		if (0 == rand() % 2)
		{
			info.key = L"bottom_knife_att_l1";
			info.MaxFrame = 6;
		}
		else
		{
			info.key = L"bottom_knife_att_l2";
			info.MaxFrame = 4;
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomKnifeAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 점프
	if (object->GetFallCheck() || input->GetKeyState(STATE_DOWN, 'S'))
		return  new PlayerBottomJumpState();

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState;

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerBottomDownState();

	return nullptr;
}

void PlayerBottomKnifeAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	object->SetSpriteInfo(info);
}
