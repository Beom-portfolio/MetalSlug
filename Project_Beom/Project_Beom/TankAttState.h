#pragma once
#include "State.h"

class TankAttState
	: public State
{
public:
	TankAttState();
	virtual ~TankAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	int m_shotTime = 0;
};



