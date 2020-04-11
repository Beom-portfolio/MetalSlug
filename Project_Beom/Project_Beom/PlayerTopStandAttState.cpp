#include "pch.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUpAttState.h"
#include "PistolBullet.h"
#include "GameObject.h"

PlayerTopStandAttState::PlayerTopStandAttState()
{
}

PlayerTopStandAttState::~PlayerTopStandAttState()
{
}

void PlayerTopStandAttState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	m_originDir = object->GetDirection();
	if (DIR_RIGHT == object->GetDirection())
	{
		info.key = L"top_stand_att_r";
		object->SetCollideInfo(GAMEOBJINFO{ 35, -18, 50, 5 });
	}
	else
	{
		info.key = L"top_stand_att_l";
		object->SetCollideInfo(GAMEOBJINFO{ -35, -18, 50, 5 });
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 9;
	info.Speed = 20.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopStandAttState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();

	// �� ����
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		if(input->GetKeyState(STATE_PUSH, 'A'))
			return new PlayerTopUpAttState();
		else
			return new PlayerTopUpState();

	// �Ʒ� ����
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// �ٽ� ����
	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopStandAttState();

	// ����
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopRunState();

	// ������ ������ Ʋ������ ����
	if (object->GetDirection() != m_originDir)
		return new PlayerTopStandState();

	// ��� ����ϸ� ����
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PlayerTopStandState();

	return nullptr;
}

void PlayerTopStandAttState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	// �Ѿ� ����
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