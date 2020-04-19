#include "pch.h"
#include "CamelIdleState.h"
#include "CamelRestState.h"
#include "CamelRunState.h"
#include "Camel.h"
#include "GameObject.h"

CamelIdleState::CamelIdleState()
{
}

CamelIdleState::~CamelIdleState()
{
}

void CamelIdleState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"camel_idle";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 3;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSize(200, 300);
}

State* CamelIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!((Camel*)object)->GetRideCheck())
		return new CamelRestState;

	if (input->GetKeyState(STATE_PUSH, VK_LEFT) || input->GetKeyState(STATE_PUSH, VK_RIGHT))
		return new CamelRunState;

	return nullptr;
}

void CamelIdleState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
