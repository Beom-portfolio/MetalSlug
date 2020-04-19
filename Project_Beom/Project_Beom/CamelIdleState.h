#pragma once
#include "State.h"

class CamelIdleState
	: public State
{
public:
	CamelIdleState();
	virtual ~CamelIdleState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};
