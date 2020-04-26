#include "pch.h"
#include "BossAttState.h"
#include "BossAttEndState.h"
#include "GameObject.h"
#include "Boss.h"
#include "FireCollider.h"

BossAttState::BossAttState()
{
}

BossAttState::~BossAttState()
{
}

void BossAttState::Enter(GameObject* object)
{
	GETMGR(SoundManager)->PlaySound(L"BossAtt.mp3", CH_MONSTER);

	GameObject* r, * l;
	((Boss*)object)->GetWings(&r, &l);
	r->SetState(BOSS_ATT);
	l->SetState(BOSS_ATT);

	POSITION objPos = object->GetPosition();

	m_originPosX = objPos.X;
	m_originPosY = objPos.Y;

	// 충돌체 생성
	m_ColliderLeft = AbstractFactory<FireCollider>::CreateObj();
	m_ColliderRight = AbstractFactory<FireCollider>::CreateObj();
	m_ColliderLeft->SetPosition(objPos.X - 262.f, objPos.Y + 150.f);
	m_ColliderRight->SetPosition(objPos.X + 278.f, objPos.Y + 150.f);
	GETMGR(ObjectManager)->AddObject(m_ColliderLeft, OBJ_MONSTER_BULLET);
	GETMGR(ObjectManager)->AddObject(m_ColliderRight, OBJ_MONSTER_BULLET);
}

State* BossAttState::HandleInput(GameObject* object, KeyManager* input)
{
	if (m_runTime >= m_attTime)
	{
		if (m_TimeStack >= 0.5f)
		{
			m_ColliderLeft->SetDead(true);
			m_ColliderRight->SetDead(true);
			object->SetPosition(m_originPosX, m_originPosY);
			return new BossAttEndState();
		}
	}

	return nullptr;
}

void BossAttState::Update(GameObject* object, const float& TimeDelta)
{
	// 충돌체가 따라다니도록
	POSITION objPos = object->GetPosition();
	m_ColliderLeft->SetPosition(objPos.X - 270.f, objPos.Y + 150.f);
	m_ColliderRight->SetPosition(objPos.X + 285.f, objPos.Y + 150.f);

	// 움직임
	m_runTime += TimeDelta;
	m_TimeStack += 0.8f * TimeDelta;

	if (m_rightCheck)
	{
		object->SetPosition(Lerp<float, float>(m_originPosX - 250.f, m_originPosX + 250.f, m_TimeStack),
			object->GetPosition().Y);

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_rightCheck = false;
		}
	}
	else
	{
		object->SetPosition(Lerp<float, float>(m_originPosX + 250.f, m_originPosX - 250.f, m_TimeStack),
			object->GetPosition().Y);

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_rightCheck = true;
		}
	}
	
	m_TimeStack2 += 3.f * TimeDelta;
	if (m_upCheck)
	{
		object->SetPosition(object->GetPosition().X,
			Lerp<float, float>(m_originPosY, m_originPosY - 25.f, m_TimeStack2));

		if (m_TimeStack2 >= 1.f)
		{
			m_TimeStack2 = 0.f;
			m_upCheck = false;
		}
	}
	else
	{
		object->SetPosition(object->GetPosition().X,
			Lerp<float, float>(m_originPosY - 25.f, m_originPosY, m_TimeStack2));

		if (m_TimeStack2 >= 1.f)
		{
			m_TimeStack2 = 0.f;
			m_upCheck = true;
		}
	}
}
