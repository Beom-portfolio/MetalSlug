#include "pch.h"
#include "PlayerBottomDownAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottom.h"
#include "PlayerBottomKnifeAttState.h"
#include "MachinegunBullet.h"
#include "GameObject.h"
#include "PistolBullet.h"
#include "Player.h"

PlayerBottomDownAttState::PlayerBottomDownAttState()
{
}

PlayerBottomDownAttState::~PlayerBottomDownAttState()
{
}

void PlayerBottomDownAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"bottom_down_att_r";
			info.MaxFrame = 5;
			object->SetCollideInfo(GAMEOBJINFO{ 30, 10, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"bottom_down_att_heavy_r";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ 50, 1, 50, 5 });
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"bottom_down_att_l";
			info.MaxFrame = 5;
			object->SetCollideInfo(GAMEOBJINFO{ -30, 10, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"bottom_down_att_heavy_l";
			info.MaxFrame = 4;
			object->SetCollideInfo(GAMEOBJINFO{ -50, 1, 50, 5 });
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSpeed(0.f);			// 플레이어 공격시에는 못움직이게 하기 위함
}

State* PlayerBottomDownAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 점프
	if (object->GetFallCheck() || input->GetKeyState(STATE_DOWN, 'S'))
	{
		object->SetSpeed(1.f);		// 플레이어 공격이 끝나면 움직이게 한다.
		return  new PlayerBottomJumpState();
	}

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
	{ 
		object->SetSpeed(1.f);
		return new PlayerBottomStandState;
	}

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (true == object->GetCollideCheck())
			return new PlayerBottomKnifeAttState();
		else
			return new PlayerBottomDownAttState();
	}

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		object->SetSpeed(1.f);
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		object->SetSpeed(1.f);
		return new PlayerBottomDownState();
	}

	return nullptr;
}

void PlayerBottomDownAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	// 총알 생성
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
				GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
				++m_count;
			}
		}
	}

	
	if (DIR_RIGHT == m_originDir)
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"bottom_down_att_r";
			info.MaxFrame = 5;
			object->SetCollideInfo(GAMEOBJINFO{ 30, 10, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"bottom_down_att_heavy_r";
			info.MaxFrame = 4;
		}
	}
	else
	{
		if (PLAYER_PISTOL == weaponType)
		{
			info.key = L"bottom_down_att_l";
			info.MaxFrame = 5;
			object->SetCollideInfo(GAMEOBJINFO{ -30, 10, 50, 5 });
		}
		else if (PLAYER_HEAVY == weaponType)
		{
			info.key = L"bottom_down_att_heavy_l";
			info.MaxFrame = 4;
		}
	}

	object->SetSpriteInfo(info);
}
