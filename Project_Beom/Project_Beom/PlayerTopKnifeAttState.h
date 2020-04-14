#pragma once
#include "State.h"

class PlayerTopKnifeAttState
	: public State
{
public:
	PlayerTopKnifeAttState();
	virtual ~PlayerTopKnifeAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION  m_originDir = DIR_END;
};


