#pragma once
#include "State.h"

class SoldierBombAttState
	: public State
{
public:
	SoldierBombAttState();
	virtual ~SoldierBombAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	GameObject* m_Player = nullptr;
};

