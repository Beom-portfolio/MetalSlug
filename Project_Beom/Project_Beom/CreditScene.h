#pragma once
class CreditScene
	: public Scene
{
public:
	CreditScene();
	virtual ~CreditScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	HWND	m_hVideo; // 동영상 재생을 하기위한 윈도우창 핸들.

};


