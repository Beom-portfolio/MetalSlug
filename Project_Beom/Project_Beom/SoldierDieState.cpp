#include "pch.h"
#include "SoldierDieState.h"
#include "Blood.h"
#include "GameObject.h"

SoldierDieState::SoldierDieState()
{
}

SoldierDieState::~SoldierDieState()
{
}

void SoldierDieState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 9;
	info.Speed = 14.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 4;

	object->SetSpriteInfo(info);
}

State* SoldierDieState::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void SoldierDieState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck)
	{
		GameObject* blood = AbstractFactory<Blood>::CreateObj(
			(int)object->GetInfo().Pos_X, (int)object->GetInfo().Pos_Y - 20);
		blood->SetDirection(object->GetDirection());
		GETMGR(ObjectManager)->AddObject(blood, OBJ_EFFECT);

		m_onceCheck = true;
	}

	if ((float)(info.MaxFrame - 1) <= info.SpriteIndex)
	{
		m_timeStack += TimeDelta;
		info.Speed = 0.f;
		if (m_timeStack >= 0.5f)
		{
			(object->GetRenderCheck()) ? object->SetRenderCheck(false) : object->SetRenderCheck(true);
			if (m_timeStack >= 1.5f)
				object->SetDead(true);
		}
	}

	object->SetSpriteInfo(info);
}
