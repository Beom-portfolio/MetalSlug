#include "pch.h"
#include "SoldierBombAttState.h"
#include "SoldierIdleState.h"
#include "GameObject.h"
#include "SoldierBomb.h"

SoldierBombAttState::SoldierBombAttState()
{
}

SoldierBombAttState::~SoldierBombAttState()
{
}

void SoldierBombAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 14;
	info.Speed = 14.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 2;

	object->SetSpriteInfo(info);

	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
}

State* SoldierBombAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new SoldierIdleState();
	
	return nullptr;
}

void SoldierBombAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 10.f <= info.SpriteIndex)
	{
		GAMEOBJINFO soldierInfo = object->GetInfo();

		GameObject* bullet = AbstractFactory<SoldierBomb>::CreateObj();
		((SoldierBomb*)bullet)->SetBombRoot(m_Player->GetPosition(), object->GetPosition());
		bullet->SetDirection(object->GetDirection());
		bullet->SetPosition(soldierInfo.Pos_X, soldierInfo.Pos_Y);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_MONSTER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
