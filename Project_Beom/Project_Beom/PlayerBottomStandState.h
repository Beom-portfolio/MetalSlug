#pragma once
#include "State.h"

class PlayerBottomStandState
	: public State
{
public:
	PlayerBottomStandState();
	virtual ~PlayerBottomStandState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);
};

