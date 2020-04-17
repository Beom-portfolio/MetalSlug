#pragma once
#include "GameObject.h"

class SaruExplosion
	: public GameObject
{
public:
	SaruExplosion();
	virtual ~SaruExplosion();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};


