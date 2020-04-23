#pragma once

class GameObject;
class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

public:
	void SetPos(float x, float y);

public:
	const POSITION& GetPos() { return m_Pos; }
	const RESOLUTION& GetResolution() { return m_Resolution; }

public:
	void SetTarget(GameObject* target);
	void SetResolution(int x, int y);
	void SetFixPos(int x, int y);
	void SetOffset(int left, int top, int right, int bottom);

public:
	int  Update(const float& TimeDelta);
	void Release();

private:
	GameObject* m_Target = nullptr;
	POSITION	m_Pos;		// 현재 카메라 위치
	POSITION	m_DestPos;	// 카메라가 이동해야 할 위치
	POSITION	m_FixPos;	// 카메라가 포커싱해야 할 위치 선정
	RECT		m_Offset;	// 포커싱 위치로 부터 범위지정
							// 포커싱 위치에서 이범위를 벗어나면 카메라 이동

	RESOLUTION	m_Resolution;

	float		m_TimeX = 0.f;	// 카메라 이동속도 보간을 위한 타임값
	float		m_TimeY = 0.f;
	float		m_Rate = 0.25f; // 타임값의 최대값(줄일수록 이동가속도 빨라짐
};

