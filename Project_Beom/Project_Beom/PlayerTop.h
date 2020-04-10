#pragma once
#include "GameObject.h"

class State;
class PlayerTop
	: public GameObject
{
public:
	PlayerTop();
	virtual ~PlayerTop();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	void HandleInput();

private:
	State* m_State = nullptr;
};

