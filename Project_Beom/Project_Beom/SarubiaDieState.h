#pragma once
#include "State.h"

class SarubiaDieState
	: public State
{
public:
	SarubiaDieState();
	virtual ~SarubiaDieState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_runTime = 0.f;
	float m_waitTime = 2.f;
};


