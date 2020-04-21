#pragma once
#include "GameObject.h"

class Fire
	: public GameObject
{
public:
	Fire();
	virtual ~Fire();

public:
	virtual void SetState(DWORD state);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

