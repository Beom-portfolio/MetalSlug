#include "pch.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopJumpAttState.h"
#include "PlayerTopDiagonalUpToStandState.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTopBombAttState.h"
#include "PistolBullet.h"
#include "MachinegunBullet.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopUpAttState::PlayerTopUpAttState()
{
}

PlayerTopUpAttState::~PlayerTopUpAttState()
{
}

void PlayerTopUpAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_up_att_r";
			info.MaxFrame = 10;
			object->SetCollideInfo(GAMEOBJINFO{ -5, -65, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_up_att_heavy_r";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ -12, -85, 5, 50 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_up_att_l";
			info.MaxFrame = 10;
			object->SetCollideInfo(GAMEOBJINFO{ 5, -65, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_up_att_heavy_l";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ 12, -85, 5, 50 });
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = GUN_SPEED;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUpAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 공격중 방향이 틀어지면 종료
	if (object->GetDirection() != m_originDir)
		return new PlayerTopUpState();

	if (!object->GetFallCheck() &&
		input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();

		if (!input->GetKeyState(STATE_PUSH, VK_UP))
		{
			if (!object->GetFallCheck())
			{
				if (PLAYER_HEAVY == weaponType)
					return new PlayerTopDiagonalUpToStandState();
				else
					return new PlayerTopStandAttState();
			}
			else
			{
				if (PLAYER_HEAVY == weaponType)
					return new PlayerTopDiagonalUpToStandState();
				else
					return new PlayerTopJumpAttState();
			}
		}
		else
		{
			if (true == object->GetCollideCheck())
				return new PlayerTopKnifeAttState();
			else
				return new PlayerTopUpAttState();
		}
	}

	// 폭탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopBombAttState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopUpState();

	return nullptr;
}

void PlayerTopUpAttState::Update(GameObject* object, const float& TimeDelta)
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
			posY = (float)object->GetOriginCollideRect().top;
			bullet->SetDirection(DIR_TOP);
			bullet->SetPosition(posX, posY);
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

				if (0 == i)
					posX = object->GetOriginCollidePosition().X;
				else
					posX = object->GetOriginCollidePosition().X + 10.f - (10.f * (i - 1));
				posY = (float)object->GetOriginCollideRect().top;

				bullet->SetAngle(90.f);
				bullet->SetDirection(DIR_TOP);
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
			info.key = L"top_up_att_r";
			info.MaxFrame = 10;
			object->SetCollideInfo(GAMEOBJINFO{ -5, -65, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_up_att_heavy_r";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ -12, -85, 5, 50 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_up_att_l";
			info.MaxFrame = 10;
			object->SetCollideInfo(GAMEOBJINFO{ 5, -65, 5, 50 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_up_att_heavy_l";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ 12, -85, 5, 50 });
		}
	}

	object->SetSpriteInfo(info);
}

