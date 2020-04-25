#pragma once
#include "GameObject.h"

enum NUMBERSTYLE
{
	NUMSTYLE_BIG,
	NUMSTYLE_SMALL,
	NUMSTYLE_NOTNUMBER
};

class Number
	: public GameObject
{
public:
	Number();
	virtual ~Number();

public:
	void SetNumberStyle(NUMBERSTYLE style);
	void SetNumber(int number) { m_numberValue = number; }

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	int m_numberValue = 0;
	UINT m_mazenta = 0;
	NUMBERSTYLE m_style = NUMSTYLE_NOTNUMBER;
};

