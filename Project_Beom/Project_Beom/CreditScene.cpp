#include "pch.h"
#include "CreditScene.h"

CreditScene::CreditScene()
{
}

CreditScene::~CreditScene()
{
}

bool CreditScene::Initialize()
{
	// MCI (Media Control Interface)
	// 오디오 및 비디오 주변 장치를 제어하는 독립적인 기능을 응용프로그램에 제공하는 인터페이스다.
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD
		, L"../Video/Ending.wmv");

	MoveWindow(m_hVideo, 0, 0, WINSIZE_X, WINSIZE_Y, FALSE);
	MCIWndPlay(m_hVideo); // 미디어 재생

	return true;
}

int CreditScene::Update(const float& TimeDelta)
{
	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_RETURN))
	{
		GETMGR(SceneManager)->ChangeSceneState(SCENE_LOGO);
		return 0;
	}

	return 0;
}

void CreditScene::Render(HDC hDC)
{
}

void CreditScene::Release()
{
	MCIWndClose(m_hVideo);
}
