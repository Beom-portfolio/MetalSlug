#pragma once
#include "GameObject.h"

class SoldierBomb
	: public GameObject
{
public:
	SoldierBomb();
	virtual ~SoldierBomb();

public:
	void SetBombRoot(POSITION dst, POSITION src);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);
private:
	float m_Gravity = 1.f;
	float m_velocityX = 0.f;
	float m_velocityY = 0.f;
	POSITION m_originPos;
};




