#pragma once
#include "State.h"

class TomaIdleState
	: public State
{
public:
	TomaIdleState();
	virtual ~TomaIdleState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	GameObject* m_Player = nullptr;
	float       m_waitTime = 0.f;
	float	    m_runTime = 0.f;
};


