#pragma once

struct DataInfo
{
	GameObject* Obj;
	MONSTERTYPE type;
};

class ToolScene
	: public Scene
{
public:
	ToolScene();
	virtual ~ToolScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	void Save();
	void Load();

private:
	GameObject* m_Dummy = nullptr;
	vector<DataInfo> m_vecData;
	float m_TimeStack = 0.f;
	bool  m_SaveCheck = false;
	bool  m_LoadCheck = false;
};

