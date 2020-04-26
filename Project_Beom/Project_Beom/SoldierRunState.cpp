#include "pch.h"
#include "SoldierRunState.h"
#include "SoldierIdleState.h"
#include "GameObject.h"

SoldierRunState::SoldierRunState()
{
}

SoldierRunState::~SoldierRunState()
{
}

void SoldierRunState::Enter(GameObject* object)
{
	POSITION playerPos = GETMGR(ObjectManager)->
		GetObjFromTag(L"Player", OBJ_PLAYER)->GetPosition();
	POSITION myInfo = object->GetPosition();

	// 너무 많이 벌어지면.. 따라간다.
	if (580 < abs(playerPos.X - myInfo.X))
	{
		if (playerPos.X > myInfo.X)
			object->SetDirection(DIR_RIGHT);
		else
			object->SetDirection(DIR_LEFT);
	}
	else
		object->SetDirection(rand() % 2 ? DIR_RIGHT : DIR_LEFT);
	
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 12;
	info.Speed = 14.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 1;

	object->SetSpriteInfo(info);

	m_maxTime = 0.5f + ((rand() % 5 + 1) / 10.f);
}

State* SoldierRunState::HandleInput(GameObject* object, KeyManager* input)
{
	if (m_runTime >= m_maxTime)
		return new SoldierIdleState();

	return nullptr;
}

void SoldierRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	m_runTime += TimeDelta;

	GAMEOBJINFO objInfo = object->GetInfo();
	if (DIR_RIGHT == m_originDir)
		object->SetPosition(objInfo.Pos_X + object->GetSpeed() * TimeDelta, objInfo.Pos_Y);
	else
		object->SetPosition(objInfo.Pos_X - object->GetSpeed() * TimeDelta, objInfo.Pos_Y);

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
