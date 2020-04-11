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
		// back
		LoadGdiImage(L"back", L"../Resources/Stage/Stage_Floor_0.bmp");
		LoadGdiImage(L"back_collider", L"../Resources/Stage/Stage_Floor_0_Collider_Info.bmp");
		// player
		LoadGdiImage(L"none",				L"../Resources/Player/none.bmp");
		// right
		LoadGdiImage(L"bottom_down_r",		L"../Resources/Player/Right/down.bmp");
		LoadGdiImage(L"bottom_down_move_r", L"../Resources/Player/Right/down_move.bmp");
		LoadGdiImage(L"bottom_jump_r",		L"../Resources/Player/Right/Bottom/jump.bmp");
		LoadGdiImage(L"bottom_jump_run_r",	L"../Resources/Player/Right/Bottom/jump_run.bmp");
		LoadGdiImage(L"bottom_run_r",		L"../Resources/Player/Right/Bottom/run.bmp");
		LoadGdiImage(L"bottom_stand_r",		L"../Resources/Player/Right/Bottom/stand.bmp");
		LoadGdiImage(L"top_jump_r",			L"../Resources/Player/Right/Top/jump.bmp");
		LoadGdiImage(L"top_jump_run_r",		L"../Resources/Player/Right/Top/jump_run.bmp");
		LoadGdiImage(L"top_run_r",			L"../Resources/Player/Right/Top/run.bmp");
		LoadGdiImage(L"top_stand_r",		L"../Resources/Player/Right/Top/stand.bmp");
		LoadGdiImage(L"top_under_r",		L"../Resources/Player/Right/Top/under.bmp");
		LoadGdiImage(L"top_up_r",			L"../Resources/Player/Right/Top/up.bmp");

		LoadGdiImage(L"top_stand_att_r", L"../Resources/Player/Right/Top/shot.bmp");
		LoadGdiImage(L"top_jump_att_r", L"../Resources/Player/Right/Top/jump_shot.bmp");
		LoadGdiImage(L"top_under_att_r", L"../Resources/Player/Right/Top/under_shot.bmp");
		LoadGdiImage(L"top_up_att_r", L"../Resources/Player/Right/Top/up_shot.bmp");
		LoadGdiImage(L"bottom_down_att_r", L"../Resources/Player/Right/down_shot.bmp");
		// left
		LoadGdiImage(L"bottom_down_l",		L"../Resources/Player/Left/down.bmp");
		LoadGdiImage(L"bottom_down_move_l", L"../Resources/Player/Left/down_move.bmp");
		LoadGdiImage(L"bottom_jump_l",		L"../Resources/Player/Left/Bottom/jump.bmp");
		LoadGdiImage(L"bottom_jump_run_l",	L"../Resources/Player/Left/Bottom/jump_run.bmp");
		LoadGdiImage(L"bottom_run_l",		L"../Resources/Player/Left/Bottom/run.bmp");
		LoadGdiImage(L"bottom_stand_l",		L"../Resources/Player/Left/Bottom/stand.bmp");
		LoadGdiImage(L"top_jump_l",			L"../Resources/Player/Left/Top/jump.bmp");
		LoadGdiImage(L"top_jump_run_l",		L"../Resources/Player/Left/Top/jump_run.bmp");
		LoadGdiImage(L"top_run_l",			L"../Resources/Player/Left/Top/run.bmp");
		LoadGdiImage(L"top_stand_l",		L"../Resources/Player/Left/Top/stand.bmp");
		LoadGdiImage(L"top_under_l",		L"../Resources/Player/Left/Top/under.bmp");
		LoadGdiImage(L"top_up_l",			L"../Resources/Player/Left/Top/up.bmp");
		
		LoadGdiImage(L"top_stand_att_l", L"../Resources/Player/Left/Top/shot.bmp");
		LoadGdiImage(L"top_jump_att_l", L"../Resources/Player/Left/Top/jump_shot.bmp");
		LoadGdiImage(L"top_under_att_l", L"../Resources/Player/Left/Top/under_shot.bmp");
		LoadGdiImage(L"top_up_att_l", L"../Resources/Player/Left/Top/up_shot.bmp");
		LoadGdiImage(L"bottom_down_att_l", L"../Resources/Player/Left/down_shot.bmp");
		// bullet
		LoadGdiImage(L"pistol_bullet", L"../Resources/Weapon/Pistol/Pistol.bmp");
		// effect
		LoadGdiImage(L"effect_pistol", L"../Resources/Effect/Normal.bmp");
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
