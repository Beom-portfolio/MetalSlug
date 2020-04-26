#pragma once
#include "State.h"

class BossDieState
	: public State
{
public:
	BossDieState();
	virtual ~BossDieState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_runTime = 0.f;
	float m_waitTime = 4.f;

	bool m_rightCheck = true;
	float m_TimeStack = 0.5f;
	float m_originPosX = 0.f;
	float m_effectStack = 0.f;
};



