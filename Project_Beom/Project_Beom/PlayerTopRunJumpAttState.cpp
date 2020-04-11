#include "pch.h"
#include "PlayerTopRunJumpAttState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopJumpRunState.h"
#include "PlayerTopUpAttState.h"
#include "PistolBullet.h"
#include "GameObject.h"

PlayerTopRunJumpAttState::PlayerTopRunJumpAttState()
{
}

PlayerTopRunJumpAttState::~PlayerTopRunJumpAttState()
{
}

void PlayerTopRunJumpAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == object->GetDirection())
	{
		info.key = L"top_jump_att_r";
		object->SetCollideInfo(GAMEOBJINFO{ 50, -18, 50, 5 });
	}
	else
	{
		info.key = L"top_jump_att_l";
		object->SetCollideInfo(GAMEOBJINFO{ -50, -18, 50, 5 });
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 9;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopRunJumpAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
		if (input->GetKeyState(STATE_PUSH, VK_UP))
			return new PlayerTopUpAttState();
		else
			return new PlayerTopRunJumpAttState();

	// 점프
	if (!object->GetFallCheck())
		return new PlayerTopJumpRunState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopJumpRunState();

	return nullptr;
}

void PlayerTopRunJumpAttState::Update(GameObject* object, const float& TimeDelta)
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
