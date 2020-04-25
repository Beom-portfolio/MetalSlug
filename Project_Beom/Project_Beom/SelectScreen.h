#pragma once
#include "GameObject.h"

class SelectScreen
	: public GameObject
{
public:
	SelectScreen();
	virtual ~SelectScreen();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

