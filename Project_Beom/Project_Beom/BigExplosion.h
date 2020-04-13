#pragma once
#include "GameObject.h"

class BigExplosion
	: public GameObject
{
public:
	BigExplosion();
	virtual ~BigExplosion();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

