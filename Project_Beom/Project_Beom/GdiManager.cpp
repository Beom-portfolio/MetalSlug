#include "pch.h"
#include "GdiManager.h"

GdiManager::GdiManager()
{
}


GdiManager::~GdiManager()
{
	ResetContainer();
}

GdiImage* GdiManager::FindImage(const TCHAR* pKey)
{
	MAPBITMAP::const_iterator iter = m_mapBmp.find(pKey);

	if (m_mapBmp.end() == iter)
		return nullptr;

	return iter->second;
}

void GdiManager::LoadImageBySceneState(SCENESTATE SceneState)
{
	// 씬에 필요한 이미지를 여기서 미리 로드해 놓는다.
	GdiManager* GdiMgr = GET_MANAGER<GdiManager>();
	switch (SceneState)
	{
	case SCENESTATE::SCENE_MENU:
		break;
	case SCENESTATE::SCENE_TEST:
		LoadGdiImage(L"back", L"../Resources/Stage/Stage_Floor_0.bmp");
		LoadGdiImage(L"back_collider", L"../Resources/Stage/Stage_Floor_0_Collider_Info.bmp");
		break;
	case SCENESTATE::SCENE_MAIN:
		// Load Image
		break;
	}
}

void GdiManager::LoadGdiImage(const TCHAR* pKey, const TCHAR* pFilePath)
{
	m_mapBmp.emplace(MAPBITMAP::value_type(pKey, (new GdiImage)->LoadGdiImage(pFilePath)));
}

void GdiManager::LoadGdiImageFromFolder(const TCHAR* pKey, bstr_t folderPath)
{
	m_mapBmp.emplace(MAPBITMAP::value_type(pKey, (new GdiImage)->LoadGdiImageFromFolder(folderPath)));
}

void GdiManager::ResetContainer()
{
	for (auto& bmp : m_mapBmp)
	{
		delete bmp.second;
		bmp.second = nullptr;
	}

	m_mapBmp.clear();
}
