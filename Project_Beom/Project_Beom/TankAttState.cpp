#include "pch.h"
#include "TankAttState.h"
#include "TankIdleState.h"
#include "GameObject.h"
#include "TankEffect.h"
#include "TankBullet.h"

TankAttState::TankAttState()
{
}

TankAttState::~TankAttState()
{
}

void TankAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"tank_att_r";
	else
		info.key = L"tank_att_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 4;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* TankAttState::HandleInput(GameObject* object, KeyManager* input)
{
	if (3 <= m_shotTime)
		return new TankIdleState();

	return nullptr;
}

void TankAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 1.f <= info.SpriteIndex)
	{
		GameObject* shotEffect = AbstractFactory<TankEffect>::CreateObj();
		GameObject* bullet = AbstractFactory<TankBullet>::CreateObj();
		POSITION shotPos;
		shotPos.Y = object->GetOriginCollidePosition().Y - 50.f;
		if (DIR_RIGHT == object->GetDirection())
		{
			shotPos.X = (float)object->GetOriginCollideRect().right + 15.f;
			shotEffect->SetDirection(DIR_RIGHT);
			bullet->SetDirection(DIR_RIGHT);
		}
		else
		{
			shotPos.X = (float)object->GetOriginCollideRect().left - 15.f;
			shotEffect->SetDirection(DIR_LEFT);
			bullet->SetDirection(DIR_LEFT);
		}
		shotEffect->SetPosition(shotPos.X, shotPos.Y);
		bullet->SetPosition(shotPos.X, shotPos.Y + 10.f);
		GETMGR(ObjectManager)->AddObject(shotEffect, OBJ_EFFECT);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_MONSTER_BULLET);
		m_onceCheck = true;
	}

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		m_onceCheck = false;
		info.SpriteIndex = 0.f;
		++m_shotTime;
	}

	object->SetSpriteInfo(info);
}
