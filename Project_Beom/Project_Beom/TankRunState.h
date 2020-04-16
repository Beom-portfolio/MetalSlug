#pragma once
#include "State.h"

class TankRunState
	: public State
{
public:
	TankRunState();
	virtual ~TankRunState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION   m_originDir = DIR_LEFT;
	GameObject* m_Player = nullptr;
};



