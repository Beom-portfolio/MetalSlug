#include "pch.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopJumpState.h"
#include "GameObject.h"
#include "KnifeBullet.h"

PlayerTopKnifeAttState::PlayerTopKnifeAttState()
{
}

PlayerTopKnifeAttState::~PlayerTopKnifeAttState()
{
}

void PlayerTopKnifeAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == m_originDir)
	{
		if (0 == rand() % 2)
			info.key = L"top_knife_att_r1";
		else
			info.key = L"top_knife_att_r2";
	}
	else
	{
		if (0 == rand() % 2)
			info.key = L"top_knife_att_l1";
		else
			info.key = L"top_knife_att_l2";
	}
	info.Type = SPRITE_ONCE;
	info.Speed = 20.f;
	info.MaxFrame = 6;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopKnifeAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// 공격중 방향이 틀어지면 종료
	if (object->GetDirection() != m_originDir)
		return new PlayerTopStandState();

	// 아래 보기
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 점프
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopJumpState();

	// 모두 재생하면 종료
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopKnifeAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 1.f <= info.SpriteIndex)
	{
		GameObject* bullet = AbstractFactory<KnifeBullet>::CreateObj();
		bullet->SetPosition(object->GetPosition().X, object->GetPosition().Y);
		if (DIR_RIGHT == m_originDir)
			bullet->SetCollideInfo(GAMEOBJINFO{ 20, 0, 75, 90 });
		else
			bullet->SetCollideInfo(GAMEOBJINFO{ -20, 0, 75, 90 });

		GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
