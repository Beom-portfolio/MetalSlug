#include "pch.h"
#include "TomaRunState.h"
#include "TomaIdleState.h"
#include "GameObject.h"

TomaRunState::TomaRunState()
{
}

TomaRunState::~TomaRunState()
{
}

void TomaRunState::Enter(GameObject* object)
{
	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
	m_originDir = object->GetDirection();
}

State* TomaRunState::HandleInput(GameObject* object, KeyManager* input)
{
	POSITION playerPos = m_Player->GetPosition();
	POSITION myPos = object->GetPosition();

	if (800.f < abs(playerPos.X - myPos.X))
		return  new TomaIdleState;

	if (10.f > abs(playerPos.X - myPos.X))
		return new TomaIdleState;

	return nullptr;
}

void TomaRunState::Update(GameObject* object, const float& TimeDelta)
{
	GAMEOBJINFO objInfo = object->GetInfo();
	object->GetPosition();

	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == m_originDir)
		info.key = L"toma_r";
	else
		info.key = L"toma_l";

	if (DIR_RIGHT == m_originDir)
		object->SetPosition(objInfo.Pos_X + object->GetSpeed() * TimeDelta, objInfo.Pos_Y);
	else
		object->SetPosition(objInfo.Pos_X - object->GetSpeed() * TimeDelta, objInfo.Pos_Y);

	object->SetSpriteInfo(info);
}
