#pragma once
#include "GameObject.h"

class State;
class Sarubia
	: public GameObject
{
public:
	Sarubia();
	virtual ~Sarubia();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);
	virtual void CollisionActivate(GameObject* collideTarget);

private:
	void AI();

private:
	State* m_State = nullptr;
};


