#pragma once
#include "GameObject.h"

class State;
class Camel
	: public GameObject
{
public:
	Camel();
	virtual ~Camel();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	void SetRideCheck(bool check) { m_rideCheck = check; }
	bool GetRideCheck() { return m_rideCheck; }

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);
	virtual void CollisionDeactivate(GameObject* collideTarget);

private:
	int UpdateInput(const float& TimeDelta);
	void HandleInput();

private:
	State* m_State = nullptr;
	bool m_rideCheck = false;
	GameObject* m_Cannon = nullptr;
	float m_onGroundPosY = 0.f;
};

