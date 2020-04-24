#include "pch.h"
#include "PlayerTopJumpBombAttState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopBombAttState.h"
#include "Bomb.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopJumpBombAttState::PlayerTopJumpBombAttState()
{
}

PlayerTopJumpBombAttState::~PlayerTopJumpBombAttState()
{
}

void PlayerTopJumpBombAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		info.key = L"top_jump_bomb_att_r";
		POSITION T = AnglePos(0.f, 0.f, 65.f, 45);
		object->SetCollideInfo(GAMEOBJINFO{ T.X, T.Y, 10, 10 });
	}
	else
	{
		info.key = L"top_jump_bomb_att_l";
		POSITION T = AnglePos(0.f, 0.f, 105.f, 45);
		object->SetCollideInfo(GAMEOBJINFO{ T.X, T.Y, 10, 10 });
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.MaxFrame = 6;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpBombAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 공격중 방향이 틀어지면 종료
	if (object->GetDirection() != m_originDir)
		return new PlayerTopStandState();

	// 공격
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) && 
		input->GetKeyState(STATE_DOWN, 'D'))
		if (object->GetFallCheck())
			return new PlayerTopJumpBombAttState();
		else
			return new PlayerTopBombAttState();

	// 아래 보기
	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		if (!object->GetFallCheck())
			return new PlayerTopDownState();
			

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		if (object->GetFallCheck())
			return new PlayerTopJumpState();
		else
			return new PlayerTopStandState();


	return nullptr;
}

void PlayerTopJumpBombAttState::Update(GameObject* object, const float& TimeDelta)
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
		bullet->SetGravitySpeed(-190);
		bullet->SetSpeed(390.f + object->GetSpeed() * 0.2f);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
