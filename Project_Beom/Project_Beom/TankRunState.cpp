#include "pch.h"
#include "TankRunState.h"
#include "TankIdleState.h"
#include "GameObject.h"

TankRunState::TankRunState()
{
}

TankRunState::~TankRunState()
{
}

void TankRunState::Enter(GameObject* object)
{
	m_Player = GETMGR(ObjectManager)->GetObjFromTag(L"Player", OBJ_PLAYER);
	POSITION playerPos = m_Player->GetPosition();
	POSITION myInfo = object->GetPosition();

	if (playerPos.X > myInfo.X)
		object->SetDirection(DIR_RIGHT);
	else
		object->SetDirection(DIR_LEFT);

	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
		info.key = L"tank_run_r";
	else
		info.key = L"tank_run_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 6;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* TankRunState::HandleInput(GameObject* object, KeyManager* input)
{
	POSITION playerPos = m_Player->GetPosition();
	POSITION myPos = object->GetPosition();

	if (300.f >= GetDistance(playerPos, myPos))
		return new TankIdleState();

	return nullptr;
}

void TankRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	GAMEOBJINFO objInfo = object->GetInfo();
	if (DIR_RIGHT == m_originDir)
		object->SetPosition(objInfo.Pos_X + object->GetSpeed() * TimeDelta, objInfo.Pos_Y);
	else
		object->SetPosition(objInfo.Pos_X - object->GetSpeed() * TimeDelta, objInfo.Pos_Y);

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
