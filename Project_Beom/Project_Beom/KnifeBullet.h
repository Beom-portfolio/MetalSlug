#pragma once
#include "GameObject.h"

class KnifeBullet
	: public GameObject
{
public:
	KnifeBullet();
	virtual ~KnifeBullet();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionActivate(GameObject* collideTarget);

private:
	int m_index = 0;
};

