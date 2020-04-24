#include "pch.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopDiagonalStandToUpState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTopBombAttState.h"
#include "PistolBullet.h"
#include "MachinegunBullet.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

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
			object->SetCollideInfo(GAMEOBJINFO{ 35, 0, 50, 5 });
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
			object->SetCollideInfo(GAMEOBJINFO{ -35, 0, 50, 5 });
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = GUN_SPEED;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopStandAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 공격중 방향이 틀어지면 종료
	if (object->GetDirection() != m_originDir)
		return new PlayerTopStandState();

	// 아래 보기
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 위 보기
	if (input->GetKeyState(STATE_PUSH, VK_UP))
	{
		PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();

		if (input->GetKeyState(STATE_DOWN, 'A'))
		{
			if(PLAYER_HEAVY == weaponType)
				return new PlayerTopDiagonalStandToUpState();
			else
				return new PlayerTopUpAttState();
		}
		else
		{
			if (PLAYER_HEAVY == weaponType)
				return new PlayerTopDiagonalStandToUpState();
			else
				return new PlayerTopUpState();
		}
	}

	// 폭탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopBombAttState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (true == object->GetCollideCheck())
			return new PlayerTopKnifeAttState();
		else
			return new PlayerTopStandAttState();
	}

	// 점프
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopJumpState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopStandAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	// 총알 생성
	// 권총
	if (PLAYER_PISTOL == weaponType)
	{
		if (!m_onceCheck && 1.f <= info.SpriteIndex)
		{
			float posX, posY;
			GameObject* bullet = AbstractFactory<PistolBullet>::CreateObj();
			if (DIR_RIGHT == m_originDir)
				posX = (float)object->GetOriginCollideRect().right;
			else
				posX = (float)object->GetOriginCollideRect().left;

			posY = object->GetOriginCollidePosition().Y;
			bullet->SetDirection(m_originDir);
			bullet->SetPosition(posX, posY);
			bullet->SetSpeed(bullet->GetSpeed() + object->GetSpeed());
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
			
			m_onceCheck = true;
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == m_count && i == (int)info.SpriteIndex)
			{
				((Player*)object->GetParent())->MinusBullet(1);

				float posX, posY;
				GameObject* bullet = AbstractFactory<MachinegunBullet>::CreateObj();
				if (DIR_RIGHT == m_originDir)
				{
					posX = (float)object->GetOriginCollideRect().right;
					bullet->SetAngle(0.f);
				}
				else
				{
					posX = (float)object->GetOriginCollideRect().left;
					bullet->SetAngle(180.f);
				}

				if(0 == i)
					posY = object->GetOriginCollidePosition().Y;
				else
					posY = object->GetOriginCollidePosition().Y + 10.f - (10.f * (i - 1));
				bullet->SetDirection(m_originDir);
				bullet->SetSpeed(bullet->GetSpeed() + object->GetSpeed());
				bullet->SetPosition(posX, posY);
				GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
				++m_count;
			}
		}
	}

	
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
			object->SetCollideInfo(GAMEOBJINFO{ 35, 0, 50, 5 });
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
			object->SetCollideInfo(GAMEOBJINFO{ -35, 0, 50, 5 });
		}
	}

	object->SetSpriteInfo(info);
}
