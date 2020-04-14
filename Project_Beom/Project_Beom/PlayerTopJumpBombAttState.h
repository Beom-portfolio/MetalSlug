#pragma once
#include "State.h"

class PlayerTopJumpBombAttState
	: public State
{
public:
	PlayerTopJumpBombAttState();
	virtual ~PlayerTopJumpBombAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION  m_originDir = DIR_END;
};



