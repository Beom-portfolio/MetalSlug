#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Release();
}

bool SceneManager::ChangeSceneState(SCENESTATE SceneState)
{
	if (nullptr != m_Scene)
	{
		Release();
	}

	switch (SceneState)
	{
	case SCENE_MENU:

		break;
	case SCENE_TEST:

		break;
	case SCENE_MAIN:

		break;
	}

	if (nullptr == m_Scene)
		return false;

	if (false == m_Scene->Initialize())
	{
		MessageBox(g_hWnd, L"씬 초기화 실패!", L"Error", MB_OK);
		Release();
		return false;
	}

	m_CurrentScene = SceneState;

	return true;
}

int SceneManager::Update(const float& TimeDelta)
{
	if (-1 == m_Scene->Update(TimeDelta))
		return -1;
	return 0;
}

void SceneManager::Render(HDC hDC)
{
	m_Scene->Render(hDC);
}

void SceneManager::Release()
{
	if (m_Scene)
	{
		delete m_Scene;
		m_Scene = nullptr;
	}
}
