#pragma once
#include "GameObject.h"

class Pro
	: public GameObject
{
public:
	Pro();
	virtual ~Pro();

public:
	virtual void SetState(DWORD state);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};



