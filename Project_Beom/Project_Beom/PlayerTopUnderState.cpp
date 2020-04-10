#include "pch.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopJumpState.h"
#include "GameObject.h"

PlayerTopUnderState::PlayerTopUnderState()
{
}

PlayerTopUnderState::~PlayerTopUnderState()
{
}

void PlayerTopUnderState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_under_r";
	else
		info.key = L"top_under_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 1;
	info.Speed = 1.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUnderState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopJumpState();

	if (!object->GetFallCheck())
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopUnderState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
