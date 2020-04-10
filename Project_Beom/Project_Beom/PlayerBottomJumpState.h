#pragma once
#include "State.h"

class PlayerBottomJumpState
	: public State
{
public:
	PlayerBottomJumpState();
	virtual ~PlayerBottomJumpState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

