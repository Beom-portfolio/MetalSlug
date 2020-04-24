#pragma once
#include "State.h"

class PrisonerBindState
	: public State
{
public:
	PrisonerBindState();
	virtual ~PrisonerBindState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	bool m_reverseCheck = false;
};

