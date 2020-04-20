#pragma once
#include "GameObject.h"

class Smog
	: public GameObject
{
public:
	Smog();
	virtual ~Smog();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};


