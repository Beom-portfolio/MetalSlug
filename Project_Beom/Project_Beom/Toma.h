#pragma once
#include "GameObject.h"

class State;
class Toma
	: public GameObject
{
public:
	Toma();
	virtual ~Toma();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionActivate(GameObject* collideTarget);

private:
	void AI();

private:
	State* m_State = nullptr;
};



