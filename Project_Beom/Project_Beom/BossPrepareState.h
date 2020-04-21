#pragma once
#include "State.h"

class BossPrepareState
	: public State
{
public:
	BossPrepareState();
	virtual ~BossPrepareState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

