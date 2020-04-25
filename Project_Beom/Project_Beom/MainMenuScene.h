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
};


