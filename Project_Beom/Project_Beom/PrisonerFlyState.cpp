#include "pch.h"
#include "PrisonerFlyState.h"
#include "PrisonerRunState.h"
#include "GameObject.h"

PrisonerFlyState::PrisonerFlyState()
{
}

PrisonerFlyState::~PrisonerFlyState()
{
}

void PrisonerFlyState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_fly_r";
	else
		info.key = L"prisoner_fly_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 5;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PrisonerFlyState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!object->GetFallCheck())
		return new PrisonerRunState();

	return nullptr;
}

void PrisonerFlyState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
