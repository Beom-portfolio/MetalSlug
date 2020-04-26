#pragma once

class MainMenuScene
	: public Scene
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	float m_TimeStack = 0.f;
	bool m_renderCheck = false;
	HWND	m_hVideo; // 동영상 재생을 하기위한 윈도우창 핸들.
	
};


