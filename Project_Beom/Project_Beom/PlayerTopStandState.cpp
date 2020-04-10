#include "pch.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopDownState.h"
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
	if (input->GetKeyState(STATE_PUSH, VK_SPACE))
		return new PlayerTopJumpState();

	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();
	
	if (!object->GetFallCheck())
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerTopRunState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerTopRunState();
	}

	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

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
