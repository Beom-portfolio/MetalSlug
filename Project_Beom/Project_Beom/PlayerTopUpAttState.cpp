#include "pch.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopJumpAttState.h"
#include "PistolBullet.h"
#include "GameObject.h"

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
	if (DIR_RIGHT == object->GetDirection())
	{
		info.key = L"top_up_att_r";
		object->SetCollideInfo(GAMEOBJINFO{ -5, -65, 5, 50 });
	}
	else
	{
		info.key = L"top_up_att_l";
		object->SetCollideInfo(GAMEOBJINFO{ 5, -65, 5, 50 });
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 10;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUpAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if (!object->GetFallCheck())
	{
		SPRITEINFO info = object->GetSpriteInfo();
		if (DIR_RIGHT == object->GetDirection())
		{
			info.key = L"top_up_att_r";
			object->SetCollideInfo(GAMEOBJINFO{ -5, -100, 5, 50 });
		}
		else
		{
			info.key = L"top_up_att_l";
			object->SetCollideInfo(GAMEOBJINFO{ 5, -100, 5, 50 });
		}
		object->SetSpriteInfo(info);
	}

	if (!object->GetFallCheck() &&
		input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 다시 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (!input->GetKeyState(STATE_PUSH, VK_UP))
		{
			if (!object->GetFallCheck())
				return new PlayerTopStandAttState();
			else
				return new PlayerTopJumpAttState();
		}
		else
		{
			return new PlayerTopUpAttState();
		}
	}

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopUpState();

	return nullptr;
}

void PlayerTopUpAttState::Update(GameObject* object, const float& TimeDelta)
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
				posY = (float)object->GetOriginCollideRect().top;
			}
			else
			{
				posX = object->GetOriginCollidePosition().X;
				posY = (float)object->GetOriginCollideRect().top;
			}
			bullet->SetDirection(DIR_TOP);
			bullet->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_BULLET);

			m_onceCheck = true;
		}
	}

	object->SetSpriteInfo(info);
}

