#pragma once
class TestScene
	: public Scene
{
public:
	TestScene();
	virtual ~TestScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	GameObject* m_Test = nullptr;
	GameObject* m_Player = nullptr;
	GameObject* m_Fade = nullptr;
	bool m_onceCheck = false;
	bool m_stackCheck = false;
	float m_stack = 0.f;
};

