#pragma once
#include "GameObject.h"

class Background_1
	: public GameObject
{
public:
	Background_1();
	virtual ~Background_1();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};



