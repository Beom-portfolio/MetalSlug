#pragma once
#include "GameObject.h"

class MediumExplosion
	: public GameObject
{
public:
	MediumExplosion();
	virtual ~MediumExplosion();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};


