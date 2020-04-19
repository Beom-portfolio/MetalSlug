#pragma once
#include "GameObject.h"

class CamelCannon
	: public GameObject
{
public:
	CamelCannon();
	virtual ~CamelCannon();

public:
	void SetSpriteY(float index) { m_spriteIndexY = index; }

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	int UpdateInput(const float& TimeDelta);

private:
	int m_upCheck = true;
	int m_leftCheck = true;
	float m_spriteIndexY = 0.f;
};

