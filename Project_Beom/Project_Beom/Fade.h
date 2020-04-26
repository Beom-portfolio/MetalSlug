#pragma once
#include "GameObject.h"

class Fade
	: public GameObject
{
public:
	Fade();
	virtual ~Fade();
public:
	bool GetChangeCheck() { return m_ChangeCheck; }
	void SetFade(bool check) { m_FadeInCheck = check; }
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
private:
	float m_Alpha = 0.f;
	float m_WaitAcc = 0.f;
	bool m_FadeInCheck = false;
	bool m_ChangeCheck = false;
};
