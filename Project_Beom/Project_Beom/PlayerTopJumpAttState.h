#pragma once
#include "State.h"

class PlayerTopJumpAttState
	: public State
{
public:
	PlayerTopJumpAttState();
	virtual ~PlayerTopJumpAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION  m_originDir = DIR_END;
	int m_count = 0;
};




