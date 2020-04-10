#pragma once
#include "State.h"

class PlayerTopJumpRunState
	: public State
{
public:
	PlayerTopJumpRunState();
	virtual ~PlayerTopJumpRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

