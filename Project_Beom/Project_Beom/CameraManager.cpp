#include "pch.h"
#include "CameraManager.h"

#include "GameObject.h"

CameraManager::CameraManager()
{
	ZeroMemory(&m_Pos, sizeof(POSITION));
	ZeroMemory(&m_Resolution, sizeof(RESOLUTION));
	ZeroMemory(&m_DestPos, sizeof(POSITION));

	// 카메라 움직임 기준을 정중앙으로 놓는다.
	m_FixPos = POSITION{ WINSIZE_X / 2, WINSIZE_Y / 2 };
	m_Offset = RECT{ 100, 100, 100, 100 };
	
}

CameraManager::~CameraManager()
{
	Release();
}

void CameraManager::SetPos(float x, float y)
{
	m_Pos.X = x;
	m_Pos.Y = y;

	if (0.f <= m_Pos.X) m_Pos.X = 0.f;
	if (0.f <= m_Pos.Y) m_Pos.Y = 0.f;
	if (-m_Resolution.X > m_Pos.X - (int)WINSIZE_X) m_Pos.X = -float(m_Resolution.X - (int)WINSIZE_X);
	if (-m_Resolution.Y > m_Pos.Y - (int)WINSIZE_Y) m_Pos.Y = -float(m_Resolution.Y - (int)WINSIZE_Y);
}

void CameraManager::SetTarget(GameObject* target)
{
	m_Target = target;

	// 타겟을 정함과 동시에 타겟의 위치를 미리 Set
	GAMEOBJINFO targetInfo = m_Target->GetInfo();
	m_Pos.X = -float(targetInfo.Pos_X - ((int)WINSIZE_X / 2));
	m_Pos.Y = -float(targetInfo.Pos_Y - ((int)WINSIZE_Y / 2));
}

void CameraManager::SetResolution(int x, int y)
{
	// 백그라운드 텍스쳐의 크기이다.
	m_Resolution.X = (float)x;
	m_Resolution.Y = (float)y;
}

void CameraManager::SetFixPos(int x, int y)
{
	m_FixPos = POSITION{ (float)x, (float)y };
}

void CameraManager::SetOffset(int left, int top, int right, int bottom)
{
	m_Offset = RECT{ left, top, right, bottom };
}

int CameraManager::Update(const float& TimeDelta)
{
	// 범위를 계산한다.
	RECT r = RECT{ (LONG)m_FixPos.X - m_Offset.left,
		(LONG)m_FixPos.Y - m_Offset.top,
		(LONG)m_FixPos.X + m_Offset.right,
		(LONG)m_FixPos.Y + m_Offset.bottom };


	if (nullptr != m_Target)
	{
		bool checkX = false;
		bool checkY = false;

		float X = -m_Target->GetInfo().Pos_X;
		float Y = -m_Target->GetInfo().Pos_Y;

		// 범위를 벗어나면 목표 위치를 설정한다.
		// X
		if (m_Target->GetTotalPosition().X < r.left)
		{
			X += r.left;
			m_DestPos.X = X;
			checkX = true;
		}

		if (m_Target->GetTotalPosition().X > r.right)
		{
			X += r.right;
			m_DestPos.X = X;
			checkX = true;
		}

		// Y
		if (m_Target->GetTotalPosition().Y < r.top)
		{
			Y += r.top;
			m_DestPos.Y = Y;
			checkY = true;
		}

		if (m_Target->GetTotalPosition().Y > r.bottom)
		{
			Y += r.bottom;
			m_DestPos.Y = Y;
			checkY = true;
		}

		// 범위를 벗어난 경우 속도를 조금씩 올리기 위한 
		// 시간값을 TimeDelta에 맞게 증가시킨다.
		// X
		if (checkX)
		{
			m_TimeX += TimeDelta;
			if (m_TimeX >= m_Rate) m_TimeX = m_Rate;
		}
		else
		{
			m_TimeX -= TimeDelta;
			if (m_TimeX <= 0.f) m_TimeX = 0.f;
		}
		// Y
		if (checkY)
		{
			m_TimeY += TimeDelta;
			if (m_TimeY >= m_Rate) m_TimeY = m_Rate;
		}
		else
		{
			m_TimeY -= TimeDelta;
			if (m_TimeY <= 0.f) m_TimeY = 0.f;
		}

		float pow = 1.f / m_Rate;
		float speedX = Lerp<float, float>(10.f, m_Target->GetSpeed(), m_TimeX * pow);
		float speedY = Lerp<float, float>(10.f, m_Target->GetSpeed(), m_TimeY * pow);
		// 가야하는 Direction 벡터를 구하여 그 방향으로 가도록 계산한다.
		POSITION Dir = m_DestPos - m_Pos;
		float Length = sqrt(Dir.X * Dir.X + Dir.Y * Dir.Y);
		POSITION totalDir = POSITION{ 0.f, 0.f };

		if (0.f != Length)
		{
			totalDir.X = Dir.X / Length;
			totalDir.Y = Dir.Y / Length;
		}

		m_Pos.X += totalDir.X * 2.f * speedX * TimeDelta;
		m_Pos.Y += totalDir.Y * 2.f * speedY * TimeDelta;
		
		if (Length <= 5.f)
		{
			m_TimeX = 0.f;
			m_TimeY = 0.f;
			m_Pos = m_DestPos;
		}

		if (0.f <= m_Pos.X) m_Pos.X = 0.f;
		if (0.f <= m_Pos.Y) m_Pos.Y = 0.f;
		if (-m_Resolution.X > m_Pos.X - (int)WINSIZE_X) m_Pos.X = -float(m_Resolution.X - (int)WINSIZE_X);
		if (-m_Resolution.Y > m_Pos.Y - (int)WINSIZE_Y) m_Pos.Y = -float(m_Resolution.Y - (int)WINSIZE_Y);
	}

	return 0;
}

void CameraManager::Release()
{
	m_Target = nullptr;
}
