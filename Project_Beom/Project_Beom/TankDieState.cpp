#include "pch.h"
#include "TankDieState.h"
#include "GameObject.h"
#include "Explosion.h"


TankDieState::TankDieState()
{
}

TankDieState::~TankDieState()
{
}

void TankDieState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"tank_dead_r";
	else
		info.key = L"tank_dead_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 13;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* TankDieState::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void TankDieState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (m_waitTime <= m_runTime)
	{
		GameObject* effect = AbstractFactory<Explosion>::CreateObj();
		effect->SetPosition(object->GetPosition().X, object->GetPosition().Y - 55.f);
		GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
		object->SetDead(true);
	}

	if ((float)(info.MaxFrame - 2) <= info.SpriteIndex)
	{
		info.Speed = 0.f;
		m_runTime += TimeDelta;
	}

	object->SetSpriteInfo(info);
}
