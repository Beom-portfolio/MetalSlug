#pragma once
#include "State.h"

class PlayerTopBombAttState
	: public State
{
public:
	PlayerTopBombAttState();
	virtual ~PlayerTopBombAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION  m_originDir = DIR_END;
};

