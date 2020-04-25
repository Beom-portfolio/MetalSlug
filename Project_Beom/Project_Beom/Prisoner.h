#pragma once
#include "GameObject.h"

class State;
class Prisoner
	: public GameObject
{
public:
	Prisoner();
	virtual ~Prisoner();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);
private:
	void AI();

private:
	State* m_State = nullptr;
	bool m_onceCheck = false;
};

