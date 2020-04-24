#include "pch.h"
#include "PlayerTopJumpAttState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUnderAttState.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopDiagonalStandToUpState.h"
#include "PlayerTopDiagonalStandToDownState.h"
#include "PlayerTopJumpBombAttState.h"
#include "PistolBullet.h"
#include "MachinegunBullet.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopJumpAttState::PlayerTopJumpAttState()
{
}

PlayerTopJumpAttState::~PlayerTopJumpAttState()
{
}

void PlayerTopJumpAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_jump_att_r";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ 50, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_jump_att_heavy_r";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ 50, 0, 50, 5 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_jump_att_l";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ -50, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_jump_att_heavy_l";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ -50, 0, 50, 5 });
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = GUN_SPEED;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 폭탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopJumpBombAttState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
		if (input->GetKeyState(STATE_PUSH, VK_UP))
		{
			if (PLAYER_HEAVY == weaponType)
				return new PlayerTopDiagonalStandToUpState();
			else
				return new PlayerTopUpAttState();
		}
		else if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		{
			if (PLAYER_HEAVY == weaponType)
				return new PlayerTopDiagonalStandToDownState();
			else
				return new PlayerTopUnderAttState();
		}
		else
			return new PlayerTopJumpAttState();
	}

	// 점프
	if (!object->GetFallCheck())
		return new PlayerTopJumpState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopJumpState();

	return nullptr;
}

void PlayerTopJumpAttState::Update(GameObject* object, const float& TimeDelta)
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

				if (0 == i)
					posY = object->GetOriginCollidePosition().Y;
				else
					posY = object->GetOriginCollidePosition().Y + 10.f - (10.f * (i - 1));
				bullet->SetDirection(m_originDir);
				bullet->SetPosition(posX, posY);
				bullet->SetSpeed(bullet->GetSpeed() + object->GetSpeed());
				GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
				++m_count;
			}
		}
	}

	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_jump_att_r";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ 50, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_jump_att_heavy_r";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ 50, 0, 50, 5 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"top_jump_att_l";
			info.MaxFrame = 9;
			object->SetCollideInfo(GAMEOBJINFO{ -50, -18, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"top_jump_att_heavy_l";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ -50, 0, 50, 5 });
		}
	}

	object->SetSpriteInfo(info);
}
