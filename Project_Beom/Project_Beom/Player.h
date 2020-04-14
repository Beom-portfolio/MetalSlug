#pragma once
#include "GameObject.h"

class State;
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

public:
	virtual void CollisionActivate(GameObject* collideTarget);
	virtual void CollisionDeactivate(GameObject* collideTarget);
private:
	GameObject* m_Bottom = nullptr;
	GameObject* m_Top = nullptr;
};

