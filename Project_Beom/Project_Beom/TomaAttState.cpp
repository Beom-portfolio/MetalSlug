#include "pch.h"
#include "TomaAttState.h"
#include "TomaIdleState.h"
#include "TomaBullet.h"

TomaAttState::TomaAttState()
{
}

TomaAttState::~TomaAttState()
{
}

void TomaAttState::Enter(GameObject* object)
{
}

State* TomaAttState::HandleInput(GameObject* object, KeyManager* input)
{
	if (3 <= m_attCount)
		return new TomaIdleState();

	return nullptr;
}

void TomaAttState::Update(GameObject* object, const float& TimeDelta)
{
	m_runTime += TimeDelta;
	if (m_attTime <= m_runTime)
	{
		GameObject* bullet = AbstractFactory<TomaBullet>::CreateObj();
		bullet->SetPosition(object->GetOriginCollidePosition().X, (float)object->GetOriginCollideRect().bottom);
		GETMGR(ObjectManager)->AddObject(bullet, OBJ_MONSTER_BULLET);
		m_runTime = 0.f;
		++m_attCount;
	}
}
