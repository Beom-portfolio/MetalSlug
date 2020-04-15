#include "pch.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomStandState.h"
#include "GameObject.h"

PlayerBottomJumpState::PlayerBottomJumpState()
{
}

PlayerBottomJumpState::~PlayerBottomJumpState()
{
}

void PlayerBottomJumpState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"bottom_jump_r";
	else
		info.key = L"bottom_jump_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 6;
	info.Speed = 25.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomJumpState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!object->GetFallCheck())
		return new PlayerBottomStandState();

	return nullptr;
}

void PlayerBottomJumpState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex -= 1.f;

	object->SetSpriteInfo(info);
}
