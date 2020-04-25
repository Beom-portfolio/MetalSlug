#pragma once
#include "GameObject.h"

class PistolBullet
	: public GameObject
{
public:
	PistolBullet();
	virtual ~PistolBullet();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);
};

