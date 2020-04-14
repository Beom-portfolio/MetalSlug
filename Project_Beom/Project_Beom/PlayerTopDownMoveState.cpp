#include "pch.h"
#include "PlayerTopDownMoveState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandState.h"
#include "GameObject.h"

PlayerTopDownMoveState::PlayerTopDownMoveState()
{
}

PlayerTopDownMoveState::~PlayerTopDownMoveState()
{
}

void PlayerTopDownMoveState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"none";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 1;
	info.Speed = 0;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopDownMoveState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopUnderState();

	if (object->GetFallCheck())
		return new PlayerTopStandState;

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopDownMoveState::Update(GameObject* object, const float& TimeDelta)
{
}
