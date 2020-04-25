#include "pch.h"
#include "PrisonerRunState.h"
#include "PrisonerFlyState.h"
#include "GameObject.h"

PrisonerRunState::PrisonerRunState()
{
}

PrisonerRunState::~PrisonerRunState()
{
}

void PrisonerRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_run_r";
	else
		info.key = L"prisoner_run_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 12;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSize(109, 145);
}

State* PrisonerRunState::HandleInput(GameObject* object, KeyManager* input)
{
	if (object->GetFallCheck())
		return new PrisonerFlyState();

	return nullptr;
}

void PrisonerRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	m_runTime += TimeDelta;

	POSITION pos = object->GetPosition();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (m_runTime >= m_changeDirTime)
		{
			object->SetDirection(DIR_LEFT);
			m_runTime = 0.f;
		}
		info.key = L"prisoner_run_r";
		object->SetPosition(pos.X + object->GetSpeed() * TimeDelta, pos.Y);
	}
	else
	{
		if (m_runTime >= m_changeDirTime)
		{
			object->SetDirection(DIR_RIGHT);
			m_runTime = 0.f;
		}
		info.key = L"prisoner_run_l";
		object->SetPosition(pos.X - object->GetSpeed() * TimeDelta, pos.Y);
	}

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
