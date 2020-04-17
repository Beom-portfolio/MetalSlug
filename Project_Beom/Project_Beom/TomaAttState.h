#pragma once
#include "State.h"

class TomaAttState
	: public State
{
public:
	TomaAttState();
	virtual ~TomaAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_attTime = 0.25f;
	float m_runTime = 0.f;
	int  m_attCount = 0;
};

