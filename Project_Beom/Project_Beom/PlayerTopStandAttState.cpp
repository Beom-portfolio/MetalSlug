#include "pch.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUpAttState.h"
#include "PistolBullet.h"
#include "PlayerTop.h"
#include "GameObject.h"

PlayerTopStandAttState::PlayerTopStandAttState()
{
}

PlayerTopStandAttState::~PlayerTopStandAttState()
{
}

void PlayerTopStandAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_stand_att_r";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ 35, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_stand_att_heavy_r";
			info.MaxFrame = 4;
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_stand_att_l";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ -35, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType) 
		{ 
			info.key = L"top_stand_att_heavy_l";
			info.MaxFrame = 4;
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopStandAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 위 보기
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		if(input->GetKeyState(STATE_PUSH, 'A'))
			return new PlayerTopUpAttState();
		else
			return new PlayerTopUpState();

	// 아래 보기
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopStandAttState();

	// 점프
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopRunState();

	// 공격중 방향이 틀어지면 종료
	if (object->GetDirection() != m_originDir)
		return new PlayerTopStandState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopStandAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	// 총알 생성
	if (!m_onceCheck)
	{
		if (1.f <= info.SpriteIndex)
		{
			float posX, posY;
			GameObject* bullet = AbstractFactory<PistolBullet>::CreateObj();
			if (DIR_RIGHT == m_originDir)
			{
				posX = (float)object->GetOriginCollideRect().right;
				posY = object->GetOriginCollidePosition().Y;
				bullet->SetDirection(DIR_RIGHT);
			}
			else
			{
				posX = (float)object->GetOriginCollideRect().left;
				posY = object->GetOriginCollidePosition().Y;
				bullet->SetDirection(DIR_LEFT);
			}
			bullet->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_BULLET);
			
			m_onceCheck = true;
		}
	}

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_stand_att_r";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ 35, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_stand_att_heavy_r";
			info.MaxFrame = 4;
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_stand_att_l";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ -35, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_stand_att_heavy_l";
			info.MaxFrame = 4;
		}
	}

	object->SetSpriteInfo(info);
}
