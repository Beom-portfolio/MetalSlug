#pragma once
#include "GameObject.h"

class Boss
	: public GameObject
{
public:
	Boss();
	virtual ~Boss();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	GameObject* m_RightWing = nullptr;
	GameObject* m_LeftWing = nullptr;
};

