#pragma once
#include "State.h"

class PlayerBottomDownMoveState
	: public State
{
public:
	PlayerBottomDownMoveState();
	virtual ~PlayerBottomDownMoveState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};


