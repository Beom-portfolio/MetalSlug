#include "pch.h"
#include "TankPrepareState.h"
#include "TankAttState.h"
#include "GameObject.h"

TankPrepareState::TankPrepareState()
{
}

TankPrepareState::~TankPrepareState()
{
}

void TankPrepareState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"tank_prepare_r";
	else
		info.key = L"tank_prepare_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 7;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* TankPrepareState::HandleInput(GameObject* object, KeyManager* input)
{
	if(m_waitTime <= m_runTime)
		return new TankAttState();

	return nullptr;
}

void TankPrepareState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)(info.MaxFrame - 1) <= info.SpriteIndex)
	{
		info.Speed = 0.f;
		m_runTime += TimeDelta;
	}

	object->SetSpriteInfo(info);
}
