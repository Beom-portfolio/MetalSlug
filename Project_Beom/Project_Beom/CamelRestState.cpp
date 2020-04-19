#include "pch.h"
#include "CamelRestState.h"
#include "CamelIdleState.h"
#include "GameObject.h"
#include "Camel.h"

CamelRestState::CamelRestState()
{
}

CamelRestState::~CamelRestState()
{
}

void CamelRestState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"camel_rest";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 6;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSize(200, 250);
}

State* CamelRestState::HandleInput(GameObject* object, KeyManager* input)
{


	if (((Camel*)object)->GetRideCheck())
		return new CamelIdleState;

	return nullptr;
}

void CamelRestState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
