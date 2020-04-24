#pragma once
#include "State.h"

class PrisonerItemState
	: public State
{
public:
	PrisonerItemState();
	virtual ~PrisonerItemState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

