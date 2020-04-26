#pragma once
#include "GameObject.h"

class State;
class Boss
	: public GameObject
{
public:
	Boss();
	virtual ~Boss();

public:
	void GetWings(GameObject** right, GameObject** left);

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
	GameObject* m_RightWing = nullptr;
	GameObject* m_LeftWing = nullptr;
	State* m_State = nullptr;

	float m_OriginPosY = 0.f;
	bool m_firstCheck = true;

	bool m_isRenderPart = true;
	int m_TotalHp = 0;

	float m_TimeSpawn = 0.f;
};

