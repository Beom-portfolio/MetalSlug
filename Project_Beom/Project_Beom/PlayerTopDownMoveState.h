#pragma once
#include "State.h"

class PlayerTopDownMoveState
	: public State
{
public:
	PlayerTopDownMoveState();
	virtual ~PlayerTopDownMoveState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

