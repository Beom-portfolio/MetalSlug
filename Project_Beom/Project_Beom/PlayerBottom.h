#pragma once
#include "GameObject.h"

class State;
class PlayerBottom
	: public GameObject
{
public:
	PlayerBottom();
	virtual ~PlayerBottom();

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

