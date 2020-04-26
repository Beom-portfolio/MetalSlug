#include "pch.h"
#include "TankIdleState.h"
#include "TankRunState.h"
#include "TankPrepareState.h"
#include "GameObject.h"

TankIdleState::TankIdleState()
{
}

TankIdleState::~TankIdleState()
{
}

void TankIdleState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"tank_stand_r";
	else
		info.key = L"tank_stand_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 2;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);

	m_waitTime = 1.f + ((rand() % 20) / 10.f);
	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
}

State* TankIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (nullptr == m_Player || m_Player->GetDeadCheck())
		return nullptr;

	POSITION playerPos = m_Player->GetPosition();
	POSITION myPos = object->GetPosition();

	if (600.f < GetDistance(playerPos, myPos))
		return nullptr;

	if (500.f < GetDistance(playerPos, myPos))
		return new TankRunState();

	if (myPos.X < playerPos.X)
		object->SetDirection(DIR_RIGHT);
	else
		object->SetDirection(DIR_LEFT);

	if (m_waitTime <= m_runTime)
		return new TankPrepareState();

	return nullptr;
}

void TankIdleState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	m_runTime += TimeDelta;

	if (DIR_RIGHT == object->GetDirection())
		info.key = L"tank_stand_r";
	else
		info.key = L"tank_stand_l";

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
