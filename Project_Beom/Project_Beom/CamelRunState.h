#pragma once
#include "State.h"

class CamelRunState
	: public State
{
public:
	CamelRunState();
	virtual ~CamelRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};




