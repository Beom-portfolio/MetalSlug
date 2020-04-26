#include "pch.h"
#include "BossDieState.h"
#include "GameObject.h"
#include "Explosion.h"
#include "SaruChip.h"
#include "BigExplosion.h"

BossDieState::BossDieState()
{
}

BossDieState::~BossDieState()
{
}

void BossDieState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.key = L"boss_body_destroy";

	object->SetSpriteInfo(info);
	object->SetCollideOn(false);

	m_originPosX = object->GetPosition().X;

	// 충돌체가 생성되어 있다면 지워준다.
	GETMGR(ObjectManager)->ReleaseFromType(OBJ_MONSTER_BULLET);
}

State* BossDieState::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void BossDieState::Update(GameObject* object, const float& TimeDelta)
{
	m_runTime += TimeDelta;

	float posY = object->GetPosition().Y;
	posY += 40.f * TimeDelta;

	m_effectStack += TimeDelta;
	if (0.5f <= m_effectStack)
	{
		GETMGR(SoundManager)->PlaySound(L"Explode-2.wav", CH_MONSTER);
		m_effectStack = 0.f;
	}

	m_TimeStack += 16.8f * TimeDelta;
	if (m_rightCheck)
	{
		object->SetPosition(Lerp<float, float>(m_originPosX - 5.f, m_originPosX + 5.f, m_TimeStack),
			posY);

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_rightCheck = false;


			GameObject* effect = nullptr;
			effect = AbstractFactory<BigExplosion>::CreateObj(true);
			effect->SetPosition(object->GetInfo().Pos_X - float(rand() % 300) + float(rand() % 300),
				object->GetInfo().Pos_Y - float(rand() % 200) + float(rand() % 200));
			GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
			
		}
	}
	else
	{
		object->SetPosition(Lerp<float, float>(m_originPosX + 5.f, m_originPosX - 5.f, m_TimeStack),
			posY);

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_rightCheck = true;

			GameObject* effect = nullptr;
			effect = AbstractFactory<BigExplosion>::CreateObj(true);
			effect->SetPosition(object->GetInfo().Pos_X - float(rand() % 300) + float(rand() % 300),
				object->GetInfo().Pos_Y - float(rand() % 200) + float(rand() % 200));
			GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
		}
	}

	if (m_waitTime <= m_runTime)
	{
		POSITION objPos = object->GetPosition();
		GETMGR(SoundManager)->PlaySound(L"Explode-2.wav", CH_MONSTER);
		GETMGR(SoundManager)->PlaySound(L"Explode3.wav", CH_MONSTER);
		GETMGR(SoundManager)->PlaySound(L"Explode4.wav", CH_MONSTER);
		for (int i = 0; i < 300; ++i)
		{
			if (0 == (i % 10))
			{
				GameObject* effect = nullptr;
				effect = AbstractFactory<BigExplosion>::CreateObj(true);
				effect->SetPosition(object->GetInfo().Pos_X - float(rand() % 300) + float(rand() % 300),
					object->GetInfo().Pos_Y - float(rand() % 200) + float(rand() % 200));
				GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
			}

			GameObject* chip = AbstractFactory<SaruChip>::CreateObj();
			float posX = objPos.X + rand() % 350 - rand() % 350;
			float posY = objPos.Y + rand() % 300 - rand() % 300;
			chip->SetPosition(posX, posY);
			chip->SetGravitySpeed(-float(300 + rand() % 400));
			chip->SetSpeed(2000.f + rand() % 3000);
			GETMGR(ObjectManager)->AddObject(chip, OBJ_EFFECT);
		}
		object->SetDead(true);
	}
}
