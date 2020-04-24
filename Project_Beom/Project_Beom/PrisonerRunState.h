#pragma once
#include "State.h"

class PrisonerRunState
	: public State
{
public:
	PrisonerRunState();
	virtual ~PrisonerRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_runTime = 0.f;
	float m_changeDirTime = 1.5f;
};

