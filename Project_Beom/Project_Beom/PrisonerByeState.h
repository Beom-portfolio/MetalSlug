#pragma once
#include "State.h"

class PrisonerByeState
	: public State
{
public:
	PrisonerByeState();
	virtual ~PrisonerByeState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

