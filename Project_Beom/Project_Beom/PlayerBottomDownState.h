#pragma once
#include "State.h"

class PlayerBottomDownState
	: public State
{
public:
	PlayerBottomDownState();
	virtual ~PlayerBottomDownState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	bool m_SpriteReverseCheck = false;
};

