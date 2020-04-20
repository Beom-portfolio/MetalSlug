#pragma once
#include "GameObject.h"

class Boost
	: public GameObject
{
public:
	Boost();
	virtual ~Boost();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

