#pragma once
#include "GameObject.h"

class StageUI
	: public GameObject
{
public:
	StageUI();
	virtual ~StageUI();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};


