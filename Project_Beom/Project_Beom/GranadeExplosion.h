#pragma once
#include "GameObject.h"

class GranadeExplosion
	: public GameObject
{
public:
	GranadeExplosion();
	virtual ~GranadeExplosion();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionActivate(GameObject* collideTarget);
};



