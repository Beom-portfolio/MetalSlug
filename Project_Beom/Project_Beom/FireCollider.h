#pragma once
#include "GameObject.h"

class FireCollider
	: public GameObject
{
public:
	FireCollider();
	virtual ~FireCollider();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionActivate(GameObject* collideTarget);
};

