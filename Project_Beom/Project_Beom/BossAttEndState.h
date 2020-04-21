#pragma once
#include "State.h"

class BossAttEndState
	: public State
{
public:
	BossAttEndState();
	virtual ~BossAttEndState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};
