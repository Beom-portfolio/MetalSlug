#pragma once
#include "State.h"

class PlayerBottomJumpRunState
	: public State
{
public:
	PlayerBottomJumpRunState();
	virtual ~PlayerBottomJumpRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

