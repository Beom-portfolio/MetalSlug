#include "pch.h"
#include "PlayerTopUpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUpAttState.h"
#include "GameObject.h"

PlayerTopUpState::PlayerTopUpState()
{
}

PlayerTopUpState::~PlayerTopUpState()
{
}

void PlayerTopUpState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"top_up_r";
	else
		info.key = L"top_up_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 4;
	info.Speed = 7.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUpState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!object->GetFallCheck())
	{
		SPRITEINFO info = object->GetSpriteInfo();
		if (DIR_RIGHT == object->GetDirection())
			info.key = L"top_up_r";
		else
			info.key = L"top_up_l";
		object->SetSpriteInfo(info);
	}

	if (!object->GetFallCheck() && 
		input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	if (!input->GetKeyState(STATE_PUSH, VK_UP))	
		return new PlayerTopJumpState();

	// АјАн
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopUpAttState();

	return nullptr;
}

void PlayerTopUpState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
