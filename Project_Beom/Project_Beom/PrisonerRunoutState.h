#pragma once
#include "State.h"


class PrisonerRunoutState
	: public State
{
public:
	PrisonerRunoutState();
	virtual ~PrisonerRunoutState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};


