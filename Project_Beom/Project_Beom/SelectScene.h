#pragma once
class SelectScene
	: public Scene
{
public:
	SelectScene();
	virtual ~SelectScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	bool  m_onceCheck = false;
	bool  m_slectCheck = false;
	bool  m_endCheck = false;
	float m_TimeStack = 0.f;
	GameObject* m_marco = nullptr;
	GameObject* m_eri = nullptr;
	GameObject* m_tarma = nullptr;
	GameObject* m_fio = nullptr;
	GameObject* m_ui = nullptr;

	int m_slotIndex = -1;
};

