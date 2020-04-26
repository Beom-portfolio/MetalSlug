#include "pch.h"
#include "BossIdleState.h"
#include "BossPrepareState.h"
#include "GameObject.h"
#include "Boss.h"

BossIdleState::BossIdleState()
{
}

BossIdleState::~BossIdleState()
{
}

void BossIdleState::Enter(GameObject* object)
{
	GameObject* r, * l;
	((Boss*)object)->GetWings(&r, &l);
	r->SetState(BOSS_IDLE);
	l->SetState(BOSS_IDLE);

	m_originPosY = object->GetPosition().Y;

	m_waitTime = 3.f + ((rand() % 10) / 10.f);
}

State* BossIdleState::HandleInput(GameObject* object, KeyManager* input)
{
	if (m_upCheck && 0.f == m_TimeStack)
	{
		if (m_waitTime < m_runTime)
		{
			object->SetPosition(object->GetPosition().X, m_originPosY);
			return new BossPrepareState();
		}
	}

	return nullptr;
}

void BossIdleState::Update(GameObject* object, const float& TimeDelta)
{
	m_runTime += TimeDelta;
	m_TimeStack += 0.75f * TimeDelta;
	if (m_upCheck)
	{
		object->SetPosition(object->GetPosition().X,
			Lerp<float, float>(m_originPosY, m_originPosY - 35.f, m_TimeStack));

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_upCheck = false;
		}
	}
	else
	{
		object->SetPosition(object->GetPosition().X,
			Lerp<float, float>(m_originPosY - 35.f, m_originPosY, m_TimeStack));

		if (m_TimeStack >= 1.f)
		{
			m_TimeStack = 0.f;
			m_upCheck = true;
		}
	}
}
