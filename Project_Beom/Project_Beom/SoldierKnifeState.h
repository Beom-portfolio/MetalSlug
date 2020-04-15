#pragma once
#include "State.h"

class SoldierKnifeState
	: public State
{
public:
	SoldierKnifeState();
	virtual ~SoldierKnifeState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	DIRECTION   m_originDir = DIR_LEFT;
	bool m_SpriteReverseCheck = false;
};



