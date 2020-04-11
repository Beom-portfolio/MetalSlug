#include "pch.h"
#include "PlayerBottomDownAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomDownMoveState.h"
#include "GameObject.h"
#include "PistolBullet.h"

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
	if (DIR_RIGHT == object->GetDirection())
	{
		info.key = L"bottom_down_att_r";
		object->SetCollideInfo(GAMEOBJINFO{ 30, 10, 50, 5 });
	}
	else
	{
		info.key = L"bottom_down_att_l";
		object->SetCollideInfo(GAMEOBJINFO{ -30, 10, 50, 5 });
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 5;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomDownAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState;

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerBottomDownAttState();

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerBottomDownState();

	return nullptr;
}

void PlayerBottomDownAttState::Update(GameObject* object, const float& TimeDelta)
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

	object->SetSpriteInfo(info);
}
