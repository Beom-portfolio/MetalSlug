#pragma once
#include "State.h"

class BossIdleState
	: public State
{
public:
	BossIdleState();
	virtual ~BossIdleState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_originPosY = 0.f;
	float m_TimeStack = 0.f;
	bool m_upCheck = true;

	float       m_waitTime = 0.f;
	float	    m_runTime = 0.f;
};


