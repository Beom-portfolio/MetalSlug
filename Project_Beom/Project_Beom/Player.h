#pragma once
#include "GameObject.h"

class Player 
	: public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);
};

