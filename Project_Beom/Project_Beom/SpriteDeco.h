#pragma once
#include "GameObject.h"

class SpriteDeco
	: public GameObject
{
public:
	SpriteDeco();
	virtual ~SpriteDeco();
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

