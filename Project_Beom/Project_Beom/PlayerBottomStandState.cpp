#include "pch.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomRunState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomDownAttState.h"
#include "GameObject.h"

PlayerBottomStandState::PlayerBottomStandState()
{
}

PlayerBottomStandState::~PlayerBottomStandState()
{
}

void PlayerBottomStandState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"bottom_stand_r";
	else
		info.key = L"bottom_stand_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 1;
	info.Speed = 1.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomStandState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerBottomJumpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		if (input->GetKeyState(STATE_PUSH, 'A'))
			return new PlayerBottomDownAttState();
		else
			return new PlayerBottomDownState();

	if (input->GetKeyState(STATE_PUSH, VK_LEFT))
		return new PlayerBottomRunState();

	if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
		return new PlayerBottomRunState();

	return nullptr;
}

void PlayerBottomStandState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
