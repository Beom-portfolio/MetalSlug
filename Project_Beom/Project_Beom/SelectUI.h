#pragma once
#include "GameObject.h"

class SelectUI
	: public GameObject
{
public:
	SelectUI();
	virtual ~SelectUI();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

