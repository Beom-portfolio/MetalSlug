#include "pch.h"
#include "TomaIdleState.h"
#include "TomaRunState.h"
#include "TomaAttState.h"
#include "GameObject.h"

TomaIdleState::TomaIdleState()
{
}

TomaIdleState::~TomaIdleState()
{
}

void TomaIdleState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"toma_r";
	else
		info.key = L"toma_l";
	info.MaxFrame = 12;
	info.Speed = 10.f;
	object->SetSpriteInfo(info);

	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
}

State* TomaIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (nullptr == m_Player || m_Player->GetDeadCheck())
		return nullptr;

	POSITION playerPos = m_Player->GetPosition();
	POSITION myPos = object->GetPosition();

	if (600.f < abs(playerPos.X - myPos.X))
		return nullptr;

	if (myPos.X < playerPos.X)
		object->SetDirection(DIR_RIGHT);
	else
		object->SetDirection(DIR_LEFT);

	if (50.f > abs(playerPos.X - myPos.X))
		return new TomaAttState();

	if (50.f < abs(playerPos.X - myPos.X))
		return new TomaRunState();

	return nullptr;
}

void TomaIdleState::Update(GameObject* object, const float& TimeDelta)
{
	m_runTime += TimeDelta;
}
