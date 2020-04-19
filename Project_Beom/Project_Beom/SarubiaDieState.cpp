#include "pch.h"
#include "SarubiaDieState.h"
#include "GameObject.h"
#include "Explosion.h"
#include "SaruChip.h"

SarubiaDieState::SarubiaDieState()
{
}

SarubiaDieState::~SarubiaDieState()
{
}

void SarubiaDieState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"saru_dead_r";
	else
		info.key = L"saru_dead_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 6;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* SarubiaDieState::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void SarubiaDieState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck)
	{
		POSITION objPos = object->GetPosition();
		for (int i = 0; i < 10; ++i)
		{
			GameObject* chip = AbstractFactory<SaruChip>::CreateObj();
			float posX = objPos.X + rand() % 200 - rand() % 200;
			float posY = objPos.Y + rand() % 250 - rand() % 250;
			chip->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(chip, OBJ_PLAYER);
		}

		m_onceCheck = true;
	}

	if (m_waitTime <= m_runTime)
	{
		GameObject* effect = AbstractFactory<Explosion>::CreateObj();
		effect->SetPosition(object->GetPosition().X, object->GetPosition().Y);
		GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);

		POSITION objPos = object->GetPosition();
		for (int i = 0; i < 25; ++i)
		{
			GameObject* chip = AbstractFactory<SaruChip>::CreateObj();
			float posX = objPos.X + rand() % 200 - rand() % 200;
			float posY = objPos.Y + rand() % 250 - rand() % 250;
			chip->SetPosition(posX, posY);
			GETMGR(ObjectManager)->AddObject(chip, OBJ_PLAYER);
		}

		object->SetDead(true);
	}

	if ((float)(info.MaxFrame - 1) <= info.SpriteIndex)
	{
		info.Speed = 0.f;
		m_runTime += TimeDelta;
	}

	object->SetSpriteInfo(info);
}
