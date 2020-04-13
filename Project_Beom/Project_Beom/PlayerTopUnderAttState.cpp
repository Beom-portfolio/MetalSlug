#include "pch.h"
#include "PlayerTopUnderAttState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopJumpAttState.h"
#include "PlayerTopDiagonalDownToStandState.h"
#include "PistolBullet.h"
#include "MachinegunBullet.h"
#include "PlayerTop.h"
#include "GameObject.h"

PlayerTopUnderAttState::PlayerTopUnderAttState()
{
}

PlayerTopUnderAttState::~PlayerTopUnderAttState()
{
}

void PlayerTopUnderAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_under_att_r";
			object->SetCollideInfo(GAMEOBJINFO{ 15, 80, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_under_att_heavy_r";
			object->SetCollideInfo(GAMEOBJINFO{ 12, 50, 5, 50 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_under_att_l";
			object->SetCollideInfo(GAMEOBJINFO{ -15, 80, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_under_att_heavy_l";
			object->SetCollideInfo(GAMEOBJINFO{ -12, 50, 5, 50 });
		}
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 4;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUnderAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if (!object->GetFallCheck())
		return new PlayerTopUnderState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();

		if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		{
			if (PLAYER_HEAVY == weaponType)
				return new PlayerTopDiagonalDownToStandState();
			else
				return new PlayerTopJumpAttState();
		}
		else
		{
			return new PlayerTopUnderAttState();
		}
	}

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopUnderState();

	return nullptr;
}

void PlayerTopUnderAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();

	// 총알 생성
	if (PLAYER_PISTOL == weaponType)
	{
		if (!m_onceCheck && 1.f <= info.SpriteIndex)
		{
			float posX, posY;
			GameObject* bullet = AbstractFactory<PistolBullet>::CreateObj();
			posX = object->GetOriginCollidePosition().X;
			posY = (float)object->GetOriginCollideRect().bottom;	
			bullet->SetDirection(DIR_BOTTOM);
			bullet->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_BULLET);

			m_onceCheck = true;
		}
	}
	else
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == m_count && i == (int)info.SpriteIndex)
			{
				float posX, posY;
				GameObject* bullet = AbstractFactory<MachinegunBullet>::CreateObj();

				if (0 == i)
					posX = object->GetOriginCollidePosition().X;
				else
					posX = object->GetOriginCollidePosition().X + 10.f - (10.f * (i - 1));
				posY = (float)object->GetOriginCollideRect().bottom;
				bullet->SetAngle(270.f);
				bullet->SetDirection(DIR_BOTTOM);
				bullet->SetPosition(posX, posY);
				GETMGR(ObjectManager)->AddObject(bullet, OBJ_BULLET);
				++m_count;
			}
		}
	}


	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_under_att_r";
			object->SetCollideInfo(GAMEOBJINFO{ 15, 80, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_under_att_heavy_r";
			object->SetCollideInfo(GAMEOBJINFO{ 12, 50, 5, 50 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_under_att_l";
			object->SetCollideInfo(GAMEOBJINFO{ -15, 80, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_under_att_heavy_l";
			object->SetCollideInfo(GAMEOBJINFO{ -12, 50, 5, 50 });
		}
	}

	object->SetSpriteInfo(info);
}
