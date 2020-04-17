#pragma once
#include "State.h"

class TankPrepareState
	: public State
{
public:
	TankPrepareState();
	virtual ~TankPrepareState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_runTime = 0.f;
	float m_waitTime = 1.5f;
};

