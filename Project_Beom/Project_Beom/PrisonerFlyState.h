#pragma once
#include "State.h"

class PrisonerFlyState
	: public State
{
public:
	PrisonerFlyState();
	virtual ~PrisonerFlyState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

