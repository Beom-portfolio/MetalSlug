#include "pch.h"
#include "CameraManager.h"

#include "GameObject.h"

CameraManager::CameraManager()
{
	ZeroMemory(&m_Pos, sizeof(POSITION));
	ZeroMemory(&m_Pos, sizeof(RESOLUTION));
	ZeroMemory(&m_OldDestPos, sizeof(POSITION));
	ZeroMemory(&m_DestPos, sizeof(POSITION));

	// 카메라 움직임 기준을 정중앙으로 놓는다.
	m_Offset.X = ((float)WINSIZE_X / 2);
	m_Offset.Y = ((float)WINSIZE_Y / 2);
}

CameraManager::~CameraManager()
{
	Release();
}

void CameraManager::SetPos(int x, int y)
{
	if (nullptr == m_Target)
		return;

	m_Pos.X = -float(x - ((int)WINSIZE_X / 2));
	m_Pos.Y = -float(y - ((int)WINSIZE_Y / 2));
}

void CameraManager::SetTarget(GameObject* target)
{
	m_Target = target;

	// 타겟을 정함과 동시에 타겟의 위치를 미리 Set
	GAMEOBJINFO targetInfo = m_Target->GetInfo();
	SetPos((int)targetInfo.Pos_X, (int)targetInfo.Pos_Y);
}

void CameraManager::SetResolution(int x, int y)
{
	// 백그라운드 텍스쳐의 크기이다.
	m_Resolution.X = (float)x;
	m_Resolution.Y = (float)y;
}

void CameraManager::SetOffset(int x, int y)
{
	m_Offset.X = ((float)WINSIZE_X / 2) - (float)x;
	m_Offset.Y = ((float)WINSIZE_Y / 2) - (float)y;
}

int CameraManager::Update(const float& TimeDelta)
{
	if (nullptr != m_Target)
	{
		m_Pos.X = -m_Target->GetInfo().Pos_X;
		//m_Pos.Y = m_Target->GetInfo().Pos_Y;
	}

	return 0;
}

void CameraManager::Release()
{
	m_Target = nullptr;
}
