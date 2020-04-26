#include "pch.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "SelectScene.h"
#include "TestScene.h"
#include "ToolScene.h"
#include "LogoScene.h"
#include "CreditScene.h"
#include "StageScene.h"

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
	case SCENE_LOGO:
		m_Scene = new LogoScene;
		break;
	case SCENE_MENU:
		m_Scene = new MainMenuScene;
		break;
	case SCENE_SELECT:
		m_Scene = new SelectScene;
		break;
	case SCENE_TOOL:
		m_Scene = new ToolScene;
		break;
	case SCENE_TEST:
		m_Scene = new TestScene;
		break;
	case SCENE_STAGE:
		m_Scene = new StageScene;
		break;
	case SCENE_CREDIT:
		m_Scene = new CreditScene;
		break;
	}

	if (nullptr == m_Scene)
		return false;

	if (false == m_Scene->Initialize())
	{
		ERRORMSG(L"씬 초기화 실패!");
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
	SAFE_RELEASE(m_Scene);
}
