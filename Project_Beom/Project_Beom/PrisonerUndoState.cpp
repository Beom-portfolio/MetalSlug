#include "pch.h"
#include "PrisonerUndoState.h"
#include "PrisonerRunState.h"
#include "GameObject.h"

PrisonerUndoState::PrisonerUndoState()
{
}

PrisonerUndoState::~PrisonerUndoState()
{
}

void PrisonerUndoState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_undo_r";
	else
		info.key = L"prisoner_undo_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 4;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PrisonerUndoState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PrisonerRunState();

	return nullptr;
}

void PrisonerUndoState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	
		info.SpriteIndex += info.Speed * TimeDelta;

	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_undo_r";
	else
		info.key = L"prisoner_undo_l";

	object->SetSpriteInfo(info);
}
