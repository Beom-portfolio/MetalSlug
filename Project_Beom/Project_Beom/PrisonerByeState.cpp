#include "pch.h"
#include "PrisonerByeState.h"
#include "PrisonerRunoutState.h"
#include "GameObject.h"

PrisonerByeState::PrisonerByeState()
{
}

PrisonerByeState::~PrisonerByeState()
{
}

void PrisonerByeState::Enter(GameObject* object)
{
	GETMGR(SoundManager)->PlaySound(L"NPC_Bye.mp3", CH_VOICE);
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_bye_r";
	else
		info.key = L"prisoner_bye_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 14;
	info.Speed = 12.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PrisonerByeState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PrisonerRunoutState();

	return nullptr;
}

void PrisonerByeState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	object->SetSpriteInfo(info);
}
