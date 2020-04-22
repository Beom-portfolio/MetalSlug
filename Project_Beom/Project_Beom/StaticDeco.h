#pragma once
#include "GameObject.h"

class StaticDeco
	: public GameObject
{
public:
	StaticDeco();
	virtual ~StaticDeco();
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

