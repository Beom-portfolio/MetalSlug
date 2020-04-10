#pragma once
#include "State.h"

class PlayerTopDownState
	: public State
{
public:
	PlayerTopDownState();
	virtual ~PlayerTopDownState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};


