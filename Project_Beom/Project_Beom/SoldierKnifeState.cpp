#include "pch.h"
#include "SoldierKnifeState.h"
#include "SoldierIdleState.h"
#include "GameObject.h"
#include "KnifeBullet.h"

SoldierKnifeState::SoldierKnifeState()
{
}

SoldierKnifeState::~SoldierKnifeState()
{
}

void SoldierKnifeState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 11;
	info.Speed = 16.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 3;

	object->SetSpriteInfo(info);
}

State* SoldierKnifeState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if (m_SpriteReverseCheck && 0.f >= info.SpriteIndex)
		return new SoldierIdleState();

	return nullptr;
}

void SoldierKnifeState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	// ¼û½¬´Â ¸ð¼Ç ¿Ô´Ù°¬´Ù
	if (m_SpriteReverseCheck)
		info.SpriteIndex -= info.Speed * TimeDelta;
	else
		info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_SpriteReverseCheck && (float)info.MaxFrame <= info.SpriteIndex)
	{
		info.SpriteIndex = (float)(info.MaxFrame - 1);
		m_SpriteReverseCheck = true;
	}

	if (!m_onceCheck && 7.f <= info.SpriteIndex)
	{
		GameObject* bullet = AbstractFactory<KnifeBullet>::CreateObj();
		bullet->SetPosition(object->GetPosition().X, object->GetPosition().Y);
		if (DIR_RIGHT == object->GetDirection())
			bullet->SetCollideInfo(GAMEOBJINFO{ 60, 0, 65, 60 });
		else
			bullet->SetCollideInfo(GAMEOBJINFO{ -60, 0, 65, 60 });

		GETMGR(ObjectManager)->AddObject(bullet, OBJ_MONSTER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
