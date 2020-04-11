#include "pch.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopStandAttState.h"
#include "GameObject.h"

PlayerTopStandState::PlayerTopStandState()
{
}

PlayerTopStandState::~PlayerTopStandState()
{
}

void PlayerTopStandState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_stand_r";
	else
		info.key = L"top_stand_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 3;
	info.Speed = 5.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopStandState::HandleInput(GameObject* object, KeyManager* input)
{
	// 좌우 이동
	if (!object->GetFallCheck())
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerTopRunState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerTopRunState();
	}

	// 아래 보기
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 위로 보기
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	// 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopStandAttState();

	// 점프
	if (input->GetKeyState(STATE_PUSH, 'S'))
		return new PlayerTopJumpState();

	return nullptr;
}

void PlayerTopStandState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
