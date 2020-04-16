#pragma once
#include "GameObject.h"

class Bomb
	: public GameObject
{
public:
	Bomb();
	virtual ~Bomb();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);
	virtual void CollisionActivate(GameObject* collideTarget);
private:
	float m_AdditionalGravity = 2.5f;
};


