#pragma once
#include "GameObject.h"

class MachinegunEffect
	: public GameObject
{
public:
	MachinegunEffect();
	virtual ~MachinegunEffect();

public:
	virtual void SetDirection(DIRECTION dir);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};


