#pragma once
#include "State.h"

class PlayerBottomRunState
	: public State
{
public:
	PlayerBottomRunState();
	virtual ~PlayerBottomRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

