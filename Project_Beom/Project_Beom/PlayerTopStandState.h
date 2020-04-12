#pragma once
#include "State.h"

class PlayerTopStandState
	: public State
{
public:
	PlayerTopStandState();
	virtual ~PlayerTopStandState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	bool m_SpriteReverseCheck = false;
};

