#pragma once
#include "State.h"

class PlayerTopUpState
	: public State
{
public:
	PlayerTopUpState();
	virtual ~PlayerTopUpState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

