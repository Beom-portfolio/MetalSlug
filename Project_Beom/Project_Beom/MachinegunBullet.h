#pragma once
#include "GameObject.h"

class MachinegunBullet
	: public GameObject
{
public:
	MachinegunBullet();
	virtual ~MachinegunBullet();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);

private:
	int m_index = 0;
};

