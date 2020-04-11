#include "pch.h"
#include "PlayerTopRunState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopJumpRunState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopDownMoveState.h"
#include "PlayerTopStandAttState.h"
#include "GameObject.h"

PlayerTopRunState::PlayerTopRunState()
{
}

PlayerTopRunState::~PlayerTopRunState()
{
}

void PlayerTopRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_run_r";
	else
		info.key = L"top_run_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 12;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopRunState::HandleInput(GameObject* object, KeyManager* input)
{
	int upCheck = 0;

	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownMoveState();

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT))
		upCheck |= DIR_LEFT;
	if (!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		upCheck |= DIR_RIGHT;

	if ((upCheck & DIR_RIGHT) && (upCheck & DIR_LEFT))
		return new PlayerTopStandState();

	// АјАн
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopStandAttState();

	if (input->GetKeyState(STATE_PUSH, 'S'))
		return new PlayerTopJumpRunState();

	return nullptr;
}

void PlayerTopRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_run_r";
	else
		info.key = L"top_run_l";
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
