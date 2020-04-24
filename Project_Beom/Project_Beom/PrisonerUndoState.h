#pragma once
#include "State.h"

class PrisonerUndoState
	: public State
{
public:
	PrisonerUndoState();
	virtual ~PrisonerUndoState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};
