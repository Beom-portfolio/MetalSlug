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
	{
		ERRORMSG(pKey);
		return nullptr;
	}

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
		{
			LoadGdiImage(L"none", L"../Resources/Player/none.bmp");
			// right
			LoadGdiImage(L"bottom_down_r", L"../Resources/Player/Right/down.bmp");
			LoadGdiImage(L"bottom_down_move_r", L"../Resources/Player/Right/down_move.bmp");
			LoadGdiImage(L"bottom_jump_r", L"../Resources/Player/Right/Bottom/jump.bmp");
			LoadGdiImage(L"bottom_jump_run_r", L"../Resources/Player/Right/Bottom/jump_run.bmp");
			LoadGdiImage(L"bottom_run_r", L"../Resources/Player/Right/Bottom/run.bmp");
			LoadGdiImage(L"bottom_stand_r", L"../Resources/Player/Right/Bottom/stand.bmp");
			LoadGdiImage(L"top_jump_r", L"../Resources/Player/Right/Top/jump.bmp");
			LoadGdiImage(L"top_jump_run_r", L"../Resources/Player/Right/Top/jump_run.bmp");
			LoadGdiImage(L"top_run_r", L"../Resources/Player/Right/Top/run.bmp");
			LoadGdiImage(L"top_stand_r", L"../Resources/Player/Right/Top/stand.bmp");
			LoadGdiImage(L"top_under_r", L"../Resources/Player/Right/Top/under.bmp");
			LoadGdiImage(L"top_up_r", L"../Resources/Player/Right/Top/up.bmp");
			LoadGdiImage(L"player_dead_r", L"../Resources/Player/Right/Dead.bmp");
			LoadGdiImage(L"player_spawn_r", L"../Resources/Player/Right/Spawn.bmp");
			// pistol
			LoadGdiImage(L"top_stand_att_r", L"../Resources/Player/Right/Top/shot.bmp");
			LoadGdiImage(L"top_jump_att_r", L"../Resources/Player/Right/Top/jump_shot.bmp");
			LoadGdiImage(L"top_under_att_r", L"../Resources/Player/Right/Top/under_shot.bmp");
			LoadGdiImage(L"top_up_att_r", L"../Resources/Player/Right/Top/up_shot.bmp");
			LoadGdiImage(L"bottom_down_att_r", L"../Resources/Player/Right/down_shot.bmp");
			// heavy
			LoadGdiImage(L"top_stand_heavy_r", L"../Resources/Player/Right/Top/heavy/stand.bmp");
			LoadGdiImage(L"top_run_heavy_r", L"../Resources/Player/Right/Top/heavy/run.bmp");
			LoadGdiImage(L"top_jump_run_heavy_r", L"../Resources/Player/Right/Top/heavy/jump_run.bmp");
			LoadGdiImage(L"top_jump_heavy_r", L"../Resources/Player/Right/Top/heavy/jump.bmp");
			LoadGdiImage(L"top_up_heavy_r", L"../Resources/Player/Right/Top/heavy/up.bmp");
			LoadGdiImage(L"top_under_heavy_r", L"../Resources/Player/Right/Top/heavy/under.bmp");
			LoadGdiImage(L"bottom_down_heavy_r", L"../Resources/Player/Right/Top/heavy/down.bmp");
			LoadGdiImage(L"bottom_down_move_heavy_r", L"../Resources/Player/Right/Top/heavy/down_move.bmp");
			LoadGdiImage(L"top_stand_att_heavy_r", L"../Resources/Player/Right/Top/heavy/shot.bmp");
			LoadGdiImage(L"top_jump_att_heavy_r", L"../Resources/Player/Right/Top/heavy/jump_shot.bmp");
			LoadGdiImage(L"top_under_att_heavy_r", L"../Resources/Player/Right/Top/heavy/under_shot.bmp");
			LoadGdiImage(L"top_up_att_heavy_r", L"../Resources/Player/Right/Top/heavy/up_shot.bmp");
			LoadGdiImage(L"bottom_down_att_heavy_r", L"../Resources/Player/Right/Top/heavy/down_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_right_up", L"../Resources/Player/Right/Top/heavy/up_ru_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_up_right", L"../Resources/Player/Right/Top/heavy/up_rd_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_right_down", L"../Resources/Player/Right/Top/heavy/down_rd_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_down_right", L"../Resources/Player/Right/Top/heavy/down_ru_shot.bmp");
			// knife
			LoadGdiImage(L"top_knife_att_r1", L"../Resources/Player/Right/Top/Nife/attack1.bmp");
			LoadGdiImage(L"top_knife_att_r2", L"../Resources/Player/Right/Top/Nife/attack2.bmp");
			LoadGdiImage(L"bottom_knife_att_r1", L"../Resources/Player/Right/Top/Nife/down_attack1.bmp");
			LoadGdiImage(L"bottom_knife_att_r2", L"../Resources/Player/Right/Top/Nife/down_attack2.bmp");
			// Bomb
			LoadGdiImage(L"top_bomb_att_r", L"../Resources/Player/Right/Top/Bomb/Throw.bmp");
			LoadGdiImage(L"top_jump_bomb_att_r", L"../Resources/Player/Right/Top/Bomb/Jump_Throw.bmp");
			LoadGdiImage(L"bottom_bomb_att_r", L"../Resources/Player/Right/Top/Bomb/down_bomb.bmp");
			//
			// left
			LoadGdiImage(L"bottom_down_l", L"../Resources/Player/Left/down.bmp");
			LoadGdiImage(L"bottom_down_move_l", L"../Resources/Player/Left/down_move.bmp");
			LoadGdiImage(L"bottom_jump_l", L"../Resources/Player/Left/Bottom/jump.bmp");
			LoadGdiImage(L"bottom_jump_run_l", L"../Resources/Player/Left/Bottom/jump_run.bmp");
			LoadGdiImage(L"bottom_run_l", L"../Resources/Player/Left/Bottom/run.bmp");
			LoadGdiImage(L"bottom_stand_l", L"../Resources/Player/Left/Bottom/stand.bmp");
			LoadGdiImage(L"top_jump_l", L"../Resources/Player/Left/Top/jump.bmp");
			LoadGdiImage(L"top_jump_run_l", L"../Resources/Player/Left/Top/jump_run.bmp");
			LoadGdiImage(L"top_run_l", L"../Resources/Player/Left/Top/run.bmp");
			LoadGdiImage(L"top_stand_l", L"../Resources/Player/Left/Top/stand.bmp");
			LoadGdiImage(L"top_under_l", L"../Resources/Player/Left/Top/under.bmp");
			LoadGdiImage(L"top_up_l", L"../Resources/Player/Left/Top/up.bmp");
			LoadGdiImage(L"player_dead_l", L"../Resources/Player/Left/Dead.bmp");
			LoadGdiImage(L"player_spawn_l", L"../Resources/Player/Left/Spawn.bmp");
			// pistol
			LoadGdiImage(L"top_stand_att_l", L"../Resources/Player/Left/Top/shot.bmp");
			LoadGdiImage(L"top_jump_att_l", L"../Resources/Player/Left/Top/jump_shot.bmp");
			LoadGdiImage(L"top_under_att_l", L"../Resources/Player/Left/Top/under_shot.bmp");
			LoadGdiImage(L"top_up_att_l", L"../Resources/Player/Left/Top/up_shot.bmp");
			LoadGdiImage(L"bottom_down_att_l", L"../Resources/Player/Left/down_shot.bmp");
			// heavy
			LoadGdiImage(L"top_stand_heavy_l", L"../Resources/Player/Left/Top/heavy/stand.bmp");
			LoadGdiImage(L"top_run_heavy_l", L"../Resources/Player/Left/Top/heavy/run.bmp");
			LoadGdiImage(L"top_jump_run_heavy_l", L"../Resources/Player/Left/Top/heavy/jump_run.bmp");
			LoadGdiImage(L"top_jump_heavy_l", L"../Resources/Player/Left/Top/heavy/jump.bmp");
			LoadGdiImage(L"top_up_heavy_l", L"../Resources/Player/Left/Top/heavy/up.bmp");
			LoadGdiImage(L"top_under_heavy_l", L"../Resources/Player/Left/Top/heavy/under.bmp");
			LoadGdiImage(L"bottom_down_heavy_l", L"../Resources/Player/Left/Top/heavy/down.bmp");
			LoadGdiImage(L"bottom_down_move_heavy_l", L"../Resources/Player/Left/Top/heavy/down_move.bmp");
			LoadGdiImage(L"top_stand_att_heavy_l", L"../Resources/Player/Left/Top/heavy/shot.bmp");
			LoadGdiImage(L"top_jump_att_heavy_l", L"../Resources/Player/Left/Top/heavy/jump_shot.bmp");
			LoadGdiImage(L"top_under_att_heavy_l", L"../Resources/Player/Left/Top/heavy/under_shot.bmp");
			LoadGdiImage(L"top_up_att_heavy_l", L"../Resources/Player/Left/Top/heavy/up_shot.bmp");
			LoadGdiImage(L"bottom_down_att_heavy_l", L"../Resources/Player/Left/Top/heavy/down_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_left_up", L"../Resources/Player/Left/Top/heavy/up_lu_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_up_left", L"../Resources/Player/Left/Top/heavy/up_ld_shot.bmp");
			LoadGdiImage(L"top_diagonal_att_left_down", L"../Resources/Player/Left/Top/heavy/down_ld_shot2.bmp");
			LoadGdiImage(L"top_diagonal_att_down_left", L"../Resources/Player/Left/Top/heavy/down_lu_shot.bmp");
			// knife
			LoadGdiImage(L"top_knife_att_l1", L"../Resources/Player/Left/Top/Nife/attack1.bmp");
			LoadGdiImage(L"top_knife_att_l2", L"../Resources/Player/Left/Top/Nife/attack2.bmp");
			LoadGdiImage(L"bottom_knife_att_l1", L"../Resources/Player/Left/Top/Nife/down_attack1.bmp");
			LoadGdiImage(L"bottom_knife_att_l2", L"../Resources/Player/Left/Top/Nife/down_attack2.bmp");
			// Bomb
			LoadGdiImage(L"top_bomb_att_l", L"../Resources/Player/Left/Top/Bomb/Throw.bmp");
			LoadGdiImage(L"top_jump_bomb_att_l", L"../Resources/Player/Left/Top/Bomb/Jump_Throw.bmp");
			LoadGdiImage(L"bottom_bomb_att_l", L"../Resources/Player/Left/Top/Bomb/down_bomb.bmp");
		}
		
		// monster
		{
			//soldier
			LoadGdiImage(L"soldier_l", L"../Resources/Monster/Monster_Left.bmp");
			LoadGdiImage(L"soldier_r", L"../Resources/Monster/Monster_Right.bmp");
			//tank
			LoadGdiImage(L"tank_stand_r", L"../Resources/Monster/Tank/Right/stand.bmp");
			LoadGdiImage(L"tank_stand_l", L"../Resources/Monster/Tank/Left/stand.bmp");
			LoadGdiImage(L"tank_run_r", L"../Resources/Monster/Tank/Right/run.bmp");
			LoadGdiImage(L"tank_run_l", L"../Resources/Monster/Tank/Left/run.bmp");
			LoadGdiImage(L"tank_att_r", L"../Resources/Monster/Tank/Right/shot.bmp");
			LoadGdiImage(L"tank_att_l", L"../Resources/Monster/Tank/Left/shot.bmp");
			LoadGdiImage(L"tank_prepare_r", L"../Resources/Monster/Tank/Right/shot_preparing.bmp");
			LoadGdiImage(L"tank_prepare_l", L"../Resources/Monster/Tank/Left/shot_preparing.bmp");
			LoadGdiImage(L"tank_dead_r", L"../Resources/Monster/Tank/Right/dead.bmp");
			LoadGdiImage(L"tank_dead_l", L"../Resources/Monster/Tank/Left/dead.bmp");
			//toma
			LoadGdiImage(L"toma_r", L"../Resources/Monster/Toma/Right/stand.bmp");
			LoadGdiImage(L"toma_l", L"../Resources/Monster/Toma/Left/stand.bmp");
			//sarubi
			LoadGdiImage(L"saru_stand_r", L"../Resources/Monster/Sarubia/Right/stand.bmp");
			LoadGdiImage(L"saru_stand_l", L"../Resources/Monster/Sarubia/Left/stand.bmp");
			LoadGdiImage(L"saru_run_r", L"../Resources/Monster/Sarubia/Right/run.bmp");
			LoadGdiImage(L"saru_run_l", L"../Resources/Monster/Sarubia/Left/run.bmp");
			LoadGdiImage(L"saru_shot_r", L"../Resources/Monster/Sarubia/Right/shot.bmp");
			LoadGdiImage(L"saru_shot_l", L"../Resources/Monster/Sarubia/Left/shot.bmp");
			LoadGdiImage(L"saru_dead_r", L"../Resources/Monster/Sarubia/Right/dead.bmp");
			LoadGdiImage(L"saru_dead_l", L"../Resources/Monster/Sarubia/Left/dead.bmp");
			LoadGdiImage(L"saru_chip", L"../Resources/Monster/Sarubia/chip.bmp");
		}
		// bullet
		LoadGdiImage(L"pistol_bullet", L"../Resources/Weapon/Pistol/Pistol.bmp");
		LoadGdiImage(L"machinegun_bullet", L"../Resources/Weapon/HeavyMachine/Heavy.bmp");
		LoadGdiImage(L"bomb_bullet", L"../Resources/Weapon/Bomb/Bomb.bmp");
		LoadGdiImage(L"soldier_bomb_bullet", L"../Resources/MonsterBullet/Boom_Bullet.bmp");
		LoadGdiImage(L"tank_bullet_l", L"../Resources/MonsterBullet/left/tank_bullet.bmp");
		LoadGdiImage(L"tank_bullet_r", L"../Resources/MonsterBullet/right/tank_bullet.bmp");
		LoadGdiImage(L"toma_bullet", L"../Resources/Weapon/All/toma_bullet.bmp");
		LoadGdiImage(L"saru_bullet", L"../Resources/Weapon/All/saru_bullet.bmp");
		// effect
		LoadGdiImage(L"effect_pistol", L"../Resources/Effect/Normal.bmp");
		LoadGdiImage(L"effect_explosion", L"../Resources/Effect/explosion.bmp");
		LoadGdiImage(L"effect_medium_explosion", L"../Resources/Effect/medium_explosion.bmp");
		LoadGdiImage(L"effect_big_explosion", L"../Resources/Effect/big_explosion.bmp");
		LoadGdiImage(L"effect_granade_explosion", L"../Resources/Effect/player_bomb.bmp");
		LoadGdiImage(L"effect_machinegun_down", L"../Resources/Effect/pong_down.bmp");
		LoadGdiImage(L"effect_machinegun_up", L"../Resources/Effect/pong_up.bmp");
		LoadGdiImage(L"effect_machinegun_left", L"../Resources/Effect/pong_left.bmp");
		LoadGdiImage(L"effect_machinegun_right", L"../Resources/Effect/pong_right.bmp");
		LoadGdiImage(L"effect_blood_right", L"../Resources/Effect/Blood_Right.bmp");
		LoadGdiImage(L"effect_blood_left", L"../Resources/Effect/Blood_Left.bmp");
		LoadGdiImage(L"effect_tank_att_left", L"../Resources/Effect/tank_left_pung.bmp");
		LoadGdiImage(L"effect_tank_att_right", L"../Resources/Effect/tank_right_pung.bmp");
		LoadGdiImage(L"effect_saru_explosion", L"../Resources/Effect/slug_bomb.bmp");
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
