#pragma once
#include "GameObject.h"

class LeftWing
	: public GameObject
{
public:
	LeftWing();
	virtual ~LeftWing();

public:
	virtual void SetState(DWORD state);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void RenderAfter(HDC hdc);

private:
	GameObject* m_Boost = nullptr;
	GameObject* m_Fire = nullptr;
	GameObject* m_Pro = nullptr;
	GameObject* m_Smog = nullptr;
};


