#include "pch.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomJumpState.h"
#include "GameObject.h"

PlayerBottomDownState::PlayerBottomDownState()
{
}

PlayerBottomDownState::~PlayerBottomDownState()
{
}

void PlayerBottomDownState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"bottom_down_r";
	else
		info.key = L"bottom_down_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 4;
	info.Speed = 7.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomDownState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_PUSH, VK_LEFT))
		return new PlayerBottomDownMoveState();

	if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
		return new PlayerBottomDownMoveState();

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState;

	if (input->GetKeyState(STATE_DOWN, VK_SPACE))
		return new PlayerBottomJumpState();

	return nullptr;
}

void PlayerBottomDownState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
