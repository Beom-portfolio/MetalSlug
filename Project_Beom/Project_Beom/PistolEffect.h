#pragma once
#include "GameObject.h"

class PistolEffect
	: public GameObject
{
public:
	PistolEffect();
	virtual ~PistolEffect();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};
