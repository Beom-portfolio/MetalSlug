#include "pch.h"
#include "PlayerTopJumpRunState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopRunJumpAttState.h"
#include "PlayerTopUpAttState.h"
#include "GameObject.h"

PlayerTopJumpRunState::PlayerTopJumpRunState()
{
}

PlayerTopJumpRunState::~PlayerTopJumpRunState()
{
}

void PlayerTopJumpRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_jump_run_r";
	else
		info.key = L"top_jump_run_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 4;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpRunState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	if (!object->GetFallCheck())
		return new PlayerTopRunState();

	// АјАн
	if (input->GetKeyState(STATE_DOWN, 'A'))
		if (input->GetKeyState(STATE_PUSH, VK_UP))
			return new PlayerTopUpAttState();
		else
			return new PlayerTopRunJumpAttState();

	return nullptr;
}

void PlayerTopJumpRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex -= 1.f;

	object->SetSpriteInfo(info);
}
