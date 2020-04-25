#pragma once
#include "GameObject.h"

class Slot
	: public GameObject
{
public:
	Slot();
	virtual ~Slot();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	float m_waitTime = 0.4f + (rand() % 4) * 0.1f - (rand() % 4) * 0.1f;
};
