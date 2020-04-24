#include "pch.h"
#include "PlayerTopDiagonalDownToStandState.h"
#include "PlayerTopUnderAttState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTop.h"
#include "MachinegunBullet.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopDiagonalDownToStandState::PlayerTopDiagonalDownToStandState()
{
}

PlayerTopDiagonalDownToStandState::~PlayerTopDiagonalDownToStandState()
{
}

void PlayerTopDiagonalDownToStandState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		info.key = L"top_diagonal_att_down_right";
		info.MaxFrame = 2;
	}
	else
	{
		info.key = L"top_diagonal_att_down_left";
		info.MaxFrame = 2;
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 16.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopDiagonalDownToStandState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	if (!object->GetFallCheck())
		return new PlayerTopStandState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopJumpState();

	return nullptr;
}

void PlayerTopDiagonalDownToStandState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	for (int i = 0; i < 3; ++i)
	{
		if (i == m_count && i == (int)info.SpriteIndex)
		{
			((Player*)object->GetParent())->MinusBullet(1);

			float angle = 0.f;
			if (DIR_LEFT == m_originDir)
				angle = 270.f - (i + 1) * (90.f / 4);
			else
				angle = 270.f + (i + 1) * (90.f / 4);

			POSITION T = AnglePos(0.f, 0.f, angle, 70);
			object->SetCollideInfo(GAMEOBJINFO{ T.X, T.Y, 10, 10 });

			GameObject* bullet = AbstractFactory<MachinegunBullet>::CreateObj();
			T.X += object->GetInfo().Pos_X;
			T.Y += object->GetInfo().Pos_Y;
			bullet->SetPosition(T.X, T.Y);
			bullet->SetAngle(angle);
			GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
			++m_count;
		}
	}

	object->SetSpriteInfo(info);
}
