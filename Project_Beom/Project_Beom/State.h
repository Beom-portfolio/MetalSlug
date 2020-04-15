#pragma once

class State
{
public:
	State();
	virtual ~State();

public:
	virtual void Enter(GameObject* object);
	virtual State* HandleInput(GameObject* object, KeyManager* input);
	virtual void Update(GameObject* object, const float& TimeDelta);

protected:
	bool m_onceCheck = false;
	float m_timeStack = 0.f;
};

