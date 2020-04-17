#include "pch.h"
#include "SarubiaAttState.h"
#include "SarubiaIdleState.h"
#include "GameObject.h"
#include "TankEffect.h"
#include "SaruBullet.h"


SarubiaAttState::SarubiaAttState()
{
}

SarubiaAttState::~SarubiaAttState()
{
}

void SarubiaAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"saru_shot_r";
	else
		info.key = L"saru_shot_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 11;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* SarubiaAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new SarubiaIdleState();

	return nullptr;
}

void SarubiaAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 1.f <= info.SpriteIndex)
	{
		GameObject* shotEffect = AbstractFactory<TankEffect>::CreateObj();
		GameObject* bullet = AbstractFactory<SaruBullet>::CreateObj();
		POSITION shotPos;
		shotPos.Y = object->GetOriginCollidePosition().Y - 100.f;
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
		bullet->SetPosition(shotPos.X, shotPos.Y);
		GETMGR(ObjectManager)->AddObject(shotEffect, OBJ_EFFECT);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_MONSTER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);

}
