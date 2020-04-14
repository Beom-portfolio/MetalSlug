#pragma once
#include "GameObject.h"

class State;
class Monster
	: public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);
};



