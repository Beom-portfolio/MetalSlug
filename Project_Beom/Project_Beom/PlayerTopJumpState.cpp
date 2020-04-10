#include "pch.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUnderState.h"
#include "GameObject.h"

PlayerTopJumpState::PlayerTopJumpState()
{
}

PlayerTopJumpState::~PlayerTopJumpState()
{
}

void PlayerTopJumpState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_jump_r";
	else
		info.key = L"top_jump_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 6;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopUnderState();

	if (!object->GetFallCheck())
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopJumpState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex -= 1.f;

	object->SetSpriteInfo(info);
}
