#pragma once
#include "GameObject.h"

class Characters
	: public GameObject
{
public:
	Characters();
	virtual ~Characters();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

