#include "pch.h"
#include "PlayerBottomRunState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomJumpRunState.h"
#include "PlayerBottomDownMoveState.h"
#include "GameObject.h"

PlayerBottomRunState::PlayerBottomRunState()
{
}

PlayerBottomRunState::~PlayerBottomRunState()
{
}

void PlayerBottomRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"bottom_run_r";
	else
		info.key = L"bottom_run_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 12;
	info.Speed = 25.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomRunState::HandleInput(GameObject* object, KeyManager* input)
{
	int upCheck = 0;

	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomDownMoveState();

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT))
		upCheck |= DIR_LEFT;
	if (!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		upCheck |= DIR_RIGHT;

	if ((upCheck & DIR_RIGHT) && (upCheck & DIR_LEFT))
		return new PlayerBottomStandState();

	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerBottomJumpRunState();

	return nullptr;
}

void PlayerBottomRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"bottom_run_r";
	else
		info.key = L"bottom_run_l";
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
