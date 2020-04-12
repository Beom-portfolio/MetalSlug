#include "pch.h"
#include "PlayerTopUnderAttState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopJumpAttState.h"
#include "PistolBullet.h"
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
		if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
			return new PlayerTopJumpAttState();
		else
			return new PlayerTopUnderAttState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopUnderState();

	return nullptr;
}

void PlayerTopUnderAttState::Update(GameObject* object, const float& TimeDelta)
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
				posX = object->GetOriginCollidePosition().X;
				posY = (float)object->GetOriginCollideRect().bottom;
			}
			else
			{
				posX = object->GetOriginCollidePosition().X;
				posY = (float)object->GetOriginCollideRect().bottom;
			}
			bullet->SetDirection(DIR_BOTTOM);
			bullet->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_BULLET);

			m_onceCheck = true;
		}
	}

	object->SetSpriteInfo(info);
}
