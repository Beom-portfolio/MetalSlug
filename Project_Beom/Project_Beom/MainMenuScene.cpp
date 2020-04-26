#include "pch.h"
#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
	:Scene()
{
}

MainMenuScene::~MainMenuScene()
{
}

bool MainMenuScene::Initialize()
{
	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_MENU);

	return true;
}

int MainMenuScene::Update(const float& TimeDelta)
{
	m_TimeStack += TimeDelta;

	if (0.4f <= m_TimeStack)
	{
		m_TimeStack = 0.f;
		m_renderCheck ? m_renderCheck = false : m_renderCheck = true;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_RETURN))
	{
		GETMGR(SoundManager)->PlaySound(L"Insert_Coin.mp3", CH_EFFECT);
		GETMGR(SceneManager)->ChangeSceneState(SCENE_SELECT);
		return 0;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F1))
	{
		GETMGR(SceneManager)->ChangeSceneState(SCENE_TOOL);
		return 0;
	}

	return 0;
}

void MainMenuScene::Render(HDC hDC)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"image")->GetGdiImageDefault();

	BitBlt(hDC, 0, -20, 800, 600, hMemDC, 0, 0, SRCCOPY);

	if (m_renderCheck)
	{
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"start")->GetGdiImageDefault();

		TransparentBlt(hDC, 196, 495, 393, 22,
			hMemDC, 0, 0, 393, 22, RGB(255, 0, 255));
	}
}

void MainMenuScene::Release()
{
	Scene::Release();
}
