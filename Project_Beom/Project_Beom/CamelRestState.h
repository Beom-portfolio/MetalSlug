#pragma once
#include "State.h"

class CamelRestState
	: public State
{
public:
	CamelRestState();
	virtual ~CamelRestState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};




