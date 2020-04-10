#pragma once
#include "State.h"

class PlayerTopRunState
	: public State
{
public:
	PlayerTopRunState();
	virtual ~PlayerTopRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

