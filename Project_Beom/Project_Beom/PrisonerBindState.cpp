#include "pch.h"
#include "PrisonerBindState.h"
#include "GameObject.h"

PrisonerBindState::PrisonerBindState()
{
}

PrisonerBindState::~PrisonerBindState()
{
}

void PrisonerBindState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_bind_r";
	else
		info.key = L"prisoner_bind_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 5;
	info.Speed = 14.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PrisonerBindState::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void PrisonerBindState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if(m_reverseCheck)
		info.SpriteIndex -= info.Speed * TimeDelta;
	else
		info.SpriteIndex += info.Speed * TimeDelta;

	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_bind_r";
	else
		info.key = L"prisoner_bind_l";

	if (!m_reverseCheck && (float)info.MaxFrame - 1.f <= info.SpriteIndex)
	{
		info.SpriteIndex = (float)info.MaxFrame - 1.f;
		m_reverseCheck = true;
	}
	else if (0.f >= info.SpriteIndex)
	{
		info.SpriteIndex = 0.f;
		m_reverseCheck = false;
	}


	object->SetSpriteInfo(info);
}
