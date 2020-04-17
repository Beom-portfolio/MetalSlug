#include "pch.h"
#include "PlayerBottomKnifeAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomStandState.h"
#include "GameObject.h"
#include "KnifeBullet.h"

PlayerBottomKnifeAttState::PlayerBottomKnifeAttState()
{
}

PlayerBottomKnifeAttState::~PlayerBottomKnifeAttState()
{
}

void PlayerBottomKnifeAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		if (0 == rand() % 2)
		{
			info.key = L"bottom_knife_att_r1";
			info.MaxFrame = 6;
		}
		else
		{
			info.key = L"bottom_knife_att_r2";
			info.MaxFrame = 4;
		}
	}
	else
	{
		if (0 == rand() % 2)
		{
			info.key = L"bottom_knife_att_l1";
			info.MaxFrame = 6;
		}
		else
		{
			info.key = L"bottom_knife_att_l2";
			info.MaxFrame = 4;
		}
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;
	
	object->SetSpriteInfo(info);
	object->SetSpeed(0.f);			// 플레이어 공격시에는 못움직이게 하기 위함
}

State* PlayerBottomKnifeAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 점프
	if (object->GetFallCheck() || input->GetKeyState(STATE_DOWN, 'S'))
	{
		object->SetSpeed(1.f);
		return  new PlayerBottomJumpState();
	}

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
	{
		object->SetSpeed(1.f);
		return new PlayerBottomStandState;
	}

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
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

void PlayerBottomKnifeAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 1.f <= info.SpriteIndex)
	{
		GameObject* bullet = AbstractFactory<KnifeBullet>::CreateObj();
		bullet->SetPosition(object->GetPosition().X, object->GetPosition().Y);
		if (DIR_RIGHT == m_originDir)
			bullet->SetCollideInfo(GAMEOBJINFO{ 20, 0, 75, 75 });
		else
			bullet->SetCollideInfo(GAMEOBJINFO{ -20, 0, 75, 75 });

		GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
