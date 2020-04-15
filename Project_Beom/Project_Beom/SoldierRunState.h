#pragma once
#include "State.h"

class SoldierRunState
	: public State
{
public:
	SoldierRunState();
	virtual ~SoldierRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION   m_originDir = DIR_LEFT;
	float       m_maxTime = 0.f;
	float	    m_runTime = 0.f;
};

