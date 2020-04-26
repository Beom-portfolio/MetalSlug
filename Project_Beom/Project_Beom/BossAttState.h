#pragma once
#include "State.h"

class BossAttState
	: public State
{
public:
	BossAttState();
	virtual ~BossAttState();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

private:
	float m_runTime = 0.f;
	float m_attTime = 5.f;
	bool m_rightCheck = (rand() % 2) ? true : false;
	float m_TimeStack = 0.5f;
	float m_originPosX = 0.f;


	float m_originPosY = 0.f;
	float m_TimeStack2 = 0.f;
	bool m_upCheck = true;

	GameObject* m_ColliderLeft = nullptr;
	GameObject* m_ColliderRight = nullptr;
};

