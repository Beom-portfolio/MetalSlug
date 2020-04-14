#pragma once
#include "State.h"

class PlayerBottomKnifeAttState
	: public State
{
public:
	PlayerBottomKnifeAttState();
	virtual ~PlayerBottomKnifeAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION  m_originDir = DIR_END;
};
