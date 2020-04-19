#include "pch.h"
#include "CamelRunState.h"
#include "CamelRestState.h"
#include "CamelIdleState.h"
#include "Camel.h"
#include "GameObject.h"

CamelRunState::CamelRunState()
{
}

CamelRunState::~CamelRunState()
{
}

void CamelRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"camel_run";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 11;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSize(200, 300);
}

State* CamelRunState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!((Camel*)object)->GetRideCheck())
		return new CamelRestState;

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT) &&
		!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		return new CamelIdleState();

	return nullptr;
}

void CamelRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
