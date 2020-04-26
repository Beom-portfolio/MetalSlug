#include "pch.h"
#include "Maingame.h"

Maingame::Maingame()
{
}

Maingame::~Maingame()
{
	
}

bool Maingame::Initialize()
{
	// 사용할 매니져 초기화
	m_GdiPlusMgr = GETMGR(GdiPlusManager);
	m_SceneMgr = GETMGR(SceneManager);
	m_SoundMgr = GETMGR(SoundManager);

	//if (!m_SceneMgr->ChangeSceneState(SCENE_MENU))
	//if (!m_SceneMgr->ChangeSceneState(SCENE_TOOL))
	if (!m_SceneMgr->ChangeSceneState(SCENE_LOGO))
		return false;

	// 그릴 DC핸들을 주윈도우 핸들로 부터 가져온다.
	m_hDC = GetDC(g_hWnd);


	return true;
}

int Maingame::Update(const float& TimeDelta)
{
	if (1.f <= TimeDelta)
		return 0;

	m_SoundMgr->UpdateSound();

	if (m_SceneMgr)
	{
		if (-1 == m_SceneMgr->Update(TimeDelta))
			return -1;
	}

	return 0;
}

void Maingame::Render()
{
	// 더블 버퍼링을 하는 작업이다. 
	HDC Memhdc;
	HBITMAP Membitmap;

	// m_hDC와 호환되는 새로운 DC를 만든다.
	// 호환 : 출력장치 종류 or 그래픽 드라이버 정보
	Memhdc = CreateCompatibleDC(m_hDC);
	// 인자로 주어진 DC에 호환하는 비트맵을 생성하여 반환
	Membitmap = CreateCompatibleBitmap(m_hDC, WINSIZE_X, WINSIZE_Y);
	// Memhdc에게 GDI Object를 설정한다.
	SelectObject(Memhdc, Membitmap);

	// 장면을 그린 DC를 m_hDC에 복사한다.
	BitBlt(Memhdc, 0, 0, WINSIZE_X, WINSIZE_Y,
		m_hDC, 0, 0, SRCCOPY);

	// 그릴 코드는 이쪽에 온다.
	///////////////////////////////////////////////////
	if (m_SceneMgr)
	{
		m_SceneMgr->Render(Memhdc);
	}
	///////////////////////////////////////////////////

	// 장면을 그린 DC를 m_hDC에 복사한다.
	BitBlt(m_hDC, 0, 0, WINSIZE_X, WINSIZE_Y,
		Memhdc, 0, 0, SRCCOPY);

	DeleteObject(Membitmap);
	DeleteDC(Memhdc);
}

void Maingame::Release()
{
	m_SceneMgr->DestroyInstance();
	m_GdiPlusMgr->DestroyInstance();
	GETMGR(ObjectManager)->DestroyInstance();
	GETMGR(CameraManager)->DestroyInstance();
	GETMGR(SoundManager)->DestroyInstance();
	GETMGR(CollisionManager)->DestroyInstance();
	GETMGR(FileManager)->DestroyInstance();

	ReleaseDC(g_hWnd, m_hDC);
}
