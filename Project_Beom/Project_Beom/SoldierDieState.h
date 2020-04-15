#pragma once
#include "State.h"

class SoldierDieState
	: public State
{
public:
	SoldierDieState();
	virtual ~SoldierDieState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};
