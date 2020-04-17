#pragma once
#include "State.h"

class TomaRunState
	: public State
{
public:
	TomaRunState();
	virtual ~TomaRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	GameObject* m_Player = nullptr;
	DIRECTION m_originDir;
};

