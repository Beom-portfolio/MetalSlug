#pragma once
#include "State.h"

class PlayerTopUnderState
	: public State
{
public:
	PlayerTopUnderState();
	virtual ~PlayerTopUnderState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};
