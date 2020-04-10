#pragma once
#include "State.h"

class PlayerTopJumpState
	: public State
{
public:
	PlayerTopJumpState();
	virtual ~PlayerTopJumpState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};



