#include "pch.h"
#include "PlayerBottomBombAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomStandState.h"
#include "Bomb.h"
#include "GameObject.h"
#include "Player.h"

PlayerBottomBombAttState::PlayerBottomBombAttState()
{
}

PlayerBottomBombAttState::~PlayerBottomBombAttState()
{
}

void PlayerBottomBombAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		info.key = L"bottom_bomb_att_r";
		POSITION T = AnglePos(0.f, 0.f, 45.f, 25);
		object->SetCollideInfo(GAMEOBJINFO{ T.X, T.Y, 10, 10 });
	}
	else
	{
		info.key = L"bottom_bomb_att_l";
		POSITION T = AnglePos(0.f, 0.f, 125.f, 25);
		object->SetCollideInfo(GAMEOBJINFO{ T.X, T.Y, 10, 10 });
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.MaxFrame = 6;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSpeed(0.f);			// 플레이어 공격시에는 못움직이게 하기 위함
}

State* PlayerBottomBombAttState::HandleInput(GameObject* object, KeyManager* input)
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

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		object->SetSpeed(1.f);
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	// 공격
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) && 
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerBottomBombAttState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		object->SetSpeed(1.f);
		return new PlayerBottomDownState();
	}

	return nullptr;
}

void PlayerBottomBombAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 2.f < info.SpriteIndex)
	{
		((Player*)object->GetParent())->MinusBomb(1);

		float posX, posY;
		posX = object->GetOriginCollidePosition().X;
		posY = object->GetOriginCollidePosition().Y;

		GameObject* bullet = AbstractFactory<Bomb>::CreateObj();
		bullet->SetDirection(m_originDir);
		bullet->SetPosition(posX, posY);
		bullet->SetGravitySpeed(-200);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
