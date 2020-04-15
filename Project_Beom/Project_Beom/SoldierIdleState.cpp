#include "pch.h"
#include "SoldierIdleState.h"
#include "SoldierRunState.h"
#include "SoldierBombAttState.h"
#include "SoldierKnifeState.h"
#include "GameObject.h"

SoldierIdleState::SoldierIdleState()
{
}

SoldierIdleState::~SoldierIdleState()
{
}

void SoldierIdleState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 6;
	info.Speed = 14.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);

	m_waitTime = 1.f + ((rand() % 10) / 10.f);
	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
}

State* SoldierIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (m_Player->GetDeadCheck())
		return nullptr;
	
	GAMEOBJINFO playerInfo = m_Player->GetInfo();
	GAMEOBJINFO myInfo = object->GetInfo();

	if (myInfo.Pos_X < playerInfo.Pos_X)
		object->SetDirection(DIR_RIGHT);
	else
		object->SetDirection(DIR_LEFT);

	// �ʹ� ���������� ��� ����.
	if (400 < abs(playerInfo.Pos_X - myInfo.Pos_X))
		return new SoldierRunState();

	// �׿�
	if (m_waitTime < m_runTime)
	{
		switch (rand() % 4)
		{
		case 0:
			return new SoldierRunState();
		case 1: case 2: case 3:
			// ������ �پ������� Į���� ������.
			if (145 > abs(playerInfo.Pos_X - myInfo.Pos_X))
				return new SoldierKnifeState();
			else
				return new SoldierBombAttState();
		}
	}

	return nullptr;
}

void SoldierIdleState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	m_runTime += TimeDelta;

	if (DIR_RIGHT == object->GetDirection())
		info.key = L"soldier_r";
	else
		info.key = L"soldier_l";

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}