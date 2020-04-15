#include "pch.h"
#include "PlayerBottomBombAttState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomStandState.h"
#include "Bomb.h"
#include "GameObject.h"

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
}

State* PlayerBottomBombAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 점프
	if (object->GetFallCheck() || input->GetKeyState(STATE_DOWN, 'S'))
		return  new PlayerBottomJumpState();

	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState;

	if ((float)info.MaxFrame <= info.SpriteIndex)
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	// 공격
	if (input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerBottomBombAttState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerBottomDownState();

	return nullptr;
}

void PlayerBottomBombAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 2.f < info.SpriteIndex)
	{
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
