#include "pch.h"
#include "PlayerTopDownState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandAttState.h"
#include "GameObject.h"

PlayerTopDownState::PlayerTopDownState()
{
}

PlayerTopDownState::~PlayerTopDownState()
{
}

void PlayerTopDownState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"none";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 1;
	info.Speed = 0.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopDownState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		if (input->GetKeyState(STATE_PUSH, 'A'))
			return new PlayerTopStandAttState;
		else
			return new PlayerTopStandState;

	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopDownState();

	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopUnderState();

	if (object->GetFallCheck())
		return new PlayerTopStandState;

	return nullptr;
}

void PlayerTopDownState::Update(GameObject* object, const float& TimeDelta)
{
}
