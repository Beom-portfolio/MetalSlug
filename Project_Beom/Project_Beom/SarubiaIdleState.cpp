#include "pch.h"
#include "SarubiaIdleState.h"
#include "SarubiaRunState.h"
#include "SarubiaAttState.h"
#include "GameObject.h"

SarubiaIdleState::SarubiaIdleState()
{
}

SarubiaIdleState::~SarubiaIdleState()
{
}

void SarubiaIdleState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"saru_stand_r";
	else
		info.key = L"saru_stand_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 2;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);

	m_waitTime = 1.5f + ((rand() % 10) / 10.f);
	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
}

State* SarubiaIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (nullptr == m_Player || m_Player->GetDeadCheck())
		return nullptr;

	POSITION playerPos = m_Player->GetPosition();
	POSITION myPos = object->GetPosition();

	if (700.f < GetDistance(playerPos, myPos))
		return nullptr;

	if (600.f < GetDistance(playerPos, myPos))
		return new SarubiaRunState();

	if (myPos.X < playerPos.X)
		object->SetDirection(DIR_RIGHT);
	else
		object->SetDirection(DIR_LEFT);

	if (m_waitTime <= m_runTime)
		return new SarubiaAttState();

	return nullptr;
}

void SarubiaIdleState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;
	m_runTime += TimeDelta;

	if (DIR_RIGHT == object->GetDirection())
		info.key = L"saru_stand_r";
	else
		info.key = L"saru_stand_l";

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
