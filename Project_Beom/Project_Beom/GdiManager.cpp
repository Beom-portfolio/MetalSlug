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
	case SCENE_LOGO:
		break;
	case SCENE_MENU:
		LoadGdiImage(L"image", L"../Resources/MyMenu/Main.bmp");
		LoadGdiImage(L"start", L"../Resources/MyMenu/start.bmp");
		break;
	case SCENE_SELECT:
		LoadGdiImage(L"fade", L"../Resources/FadeBuffer.bmp");
		LoadGdiImage(L"slect_screen", L"../Resources/Select/1.bmp");
		LoadGdiImage(L"ui", L"../Resources/Select/P1.bmp");
		LoadGdiImage(L"slot_tarma", L"../Resources/Select/Tarma4.bmp");
		LoadGdiImage(L"slot", L"../Resources/Select/2.bmp");
		LoadGdiImage(L"eri", L"../Resources/Select/Eri1.bmp");
		LoadGdiImage(L"fio", L"../Resources/Select/Fio1.bmp");
		LoadGdiImage(L"marco", L"../Resources/Select/Marco1.bmp");
		LoadGdiImage(L"tarma", L"../Resources/Select/Tarma1.bmp");
		LoadGdiImage(L"eri_select", L"../Resources/Select/Eri2.bmp");
		LoadGdiImage(L"fio_select", L"../Resources/Select/Fio2.bmp");
		LoadGdiImage(L"marco_select", L"../Resources/Select/Marco2.bmp");
		LoadGdiImage(L"tarma_select", L"../Resources/Select/Tarma2.bmp");
		LoadGdiImage(L"tarma_selected", L"../Resources/Select/Tarma3.bmp");
		break;
	case SCENE_TOOL:
	{
		LoadGdiImage(L"dummy_monsters", L"../Resources/Tool/Monsters.bmp");

		// back
		LoadGdiImage(L"back", L"../Resources/Stage/stage.bmp");
		LoadGdiImage(L"back_collider", L"../Resources/Stage/stage_collider.bmp");
		LoadGdiImage(L"y_sort_1", L"../Resources/Stage/Y_Sort_1.bmp");
		LoadGdiImage(L"y_sort_2", L"../Resources/Stage/Y_Sort_2.bmp");
		LoadGdiImage(L"deco_boss", L"../Resources/Stage/Deco_Boss.bmp");
		LoadGdiImage(L"deco_boss_1", L"../Resources/Stage/Deco_Boss_1.bmp");
		LoadGdiImage(L"deco_boss_2", L"../Resources/Stage/Deco_Boss_2.bmp");

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
			//boss
			LoadGdiImage(L"boss_body_idle", L"../Resources/Monster/Boss/body.bmp");
			LoadGdiImage(L"boss_body_hit", L"../Resources/Monster/Boss/body_hit.bmp");
			LoadGdiImage(L"boss_body_destroy", L"../Resources/Monster/Boss/destroy.bmp");
			LoadGdiImage(L"boss_wing_fire_prepare", L"../Resources/Monster/Boss/fire_preparing.bmp");
			LoadGdiImage(L"boss_wing_fire_att", L"../Resources/Monster/Boss/fire_attack.bmp");
			LoadGdiImage(L"boss_wing_fire_end", L"../Resources/Monster/Boss/fire_end.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_r", L"../Resources/Monster/Boss/right_fire_stand.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_l", L"../Resources/Monster/Boss/left_fire_stand.bmp");
			LoadGdiImage(L"boss_smog_att", L"../Resources/Monster/Boss/smog_attack.bmp");
			LoadGdiImage(L"boss_smog_end", L"../Resources/Monster/Boss/smog_end.bmp");
			LoadGdiImage(L"boss_smog_prepare", L"../Resources/Monster/Boss/smog_preparing.bmp");
			LoadGdiImage(L"boss_smog_stand", L"../Resources/Monster/Boss/smog_stand.bmp");

			LoadGdiImage(L"boss_boost_l", L"../Resources/Monster/Boss/Left/boost_stand.bmp");
			LoadGdiImage(L"boss_boost_r", L"../Resources/Monster/Boss/Right/boost_stand.bmp");
			LoadGdiImage(L"boss_pro_att_l", L"../Resources/Monster/Boss/Left/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_att_r", L"../Resources/Monster/Boss/Right/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_idle_l", L"../Resources/Monster/Boss/Left/pro_stand.bmp");
			LoadGdiImage(L"boss_pro_idle_r", L"../Resources/Monster/Boss/Right/pro_stand.bmp");
		}

		// NPC
		LoadGdiImage(L"prisoner_bind_l", L"../Resources/NPC/L_bind.bmp");
		LoadGdiImage(L"prisoner_bind_r", L"../Resources/NPC/R_bind.bmp");
		LoadGdiImage(L"prisoner_undo_l", L"../Resources/NPC/L_undo.bmp");
		LoadGdiImage(L"prisoner_undo_r", L"../Resources/NPC/R_undo.bmp");
		LoadGdiImage(L"prisoner_run_l", L"../Resources/NPC/L_run.bmp");
		LoadGdiImage(L"prisoner_run_r", L"../Resources/NPC/R_run.bmp");
		LoadGdiImage(L"prisoner_item_l", L"../Resources/NPC/L_item.bmp");
		LoadGdiImage(L"prisoner_item_r", L"../Resources/NPC/R_item.bmp");
		LoadGdiImage(L"prisoner_bye_l", L"../Resources/NPC/L_bye.bmp");
		LoadGdiImage(L"prisoner_bye_r", L"../Resources/NPC/R_bye.bmp");
		LoadGdiImage(L"prisoner_runout_l", L"../Resources/NPC/L_runout.bmp");
		LoadGdiImage(L"prisoner_runout_r", L"../Resources/NPC/R_runout.bmp");
		LoadGdiImage(L"prisoner_fly_l", L"../Resources/NPC/L_fly.bmp");
		LoadGdiImage(L"prisoner_fly_r", L"../Resources/NPC/R_fly.bmp");
	}
	break;
	case SCENE_TEST:
		LoadGdiImage(L"fade", L"../Resources/FadeBuffer.bmp");
		// back
		LoadGdiImage(L"back", L"../Resources/Stage/stage.bmp");
		LoadGdiImage(L"back_collider", L"../Resources/Stage/stage_collider.bmp");
		LoadGdiImage(L"y_sort_1", L"../Resources/Stage/Y_Sort_1.bmp");
		LoadGdiImage(L"y_sort_2", L"../Resources/Stage/Y_Sort_2.bmp");
		LoadGdiImage(L"deco_boss", L"../Resources/Stage/Deco_Boss.bmp");
		LoadGdiImage(L"deco_boss_1", L"../Resources/Stage/Deco_Boss_1.bmp");
		LoadGdiImage(L"deco_boss_2", L"../Resources/Stage/Deco_Boss_2.bmp");
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
			//boss
			LoadGdiImage(L"boss_body_idle", L"../Resources/Monster/Boss/body.bmp");
			LoadGdiImage(L"boss_body_hit", L"../Resources/Monster/Boss/body_hit.bmp");
			LoadGdiImage(L"boss_body_destroy", L"../Resources/Monster/Boss/destroy.bmp");
			LoadGdiImage(L"boss_wing_fire_prepare", L"../Resources/Monster/Boss/fire_preparing.bmp");
			LoadGdiImage(L"boss_wing_fire_att", L"../Resources/Monster/Boss/fire_attack.bmp");
			LoadGdiImage(L"boss_wing_fire_end", L"../Resources/Monster/Boss/fire_end.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_r", L"../Resources/Monster/Boss/right_fire_stand.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_l", L"../Resources/Monster/Boss/left_fire_stand.bmp");
			LoadGdiImage(L"boss_smog_att", L"../Resources/Monster/Boss/smog_attack.bmp");
			LoadGdiImage(L"boss_smog_end", L"../Resources/Monster/Boss/smog_end.bmp");
			LoadGdiImage(L"boss_smog_prepare", L"../Resources/Monster/Boss/smog_preparing.bmp");
			LoadGdiImage(L"boss_smog_stand", L"../Resources/Monster/Boss/smog_stand.bmp");

			LoadGdiImage(L"boss_boost_l", L"../Resources/Monster/Boss/Left/boost_stand.bmp");
			LoadGdiImage(L"boss_boost_r", L"../Resources/Monster/Boss/Right/boost_stand.bmp");
			LoadGdiImage(L"boss_pro_att_l", L"../Resources/Monster/Boss/Left/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_att_r", L"../Resources/Monster/Boss/Right/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_idle_l", L"../Resources/Monster/Boss/Left/pro_stand.bmp");
			LoadGdiImage(L"boss_pro_idle_r", L"../Resources/Monster/Boss/Right/pro_stand.bmp");
		}

		LoadGdiImage(L"camel_rest", L"../Resources/Camel/Idle_Not_Ride.bmp");
		LoadGdiImage(L"camel_run", L"../Resources/Camel/Run.bmp");
		LoadGdiImage(L"camel_idle", L"../Resources/Camel/Idle.bmp");
		LoadGdiImage(L"player_ride", L"../Resources/Player/Ride.bmp");
		LoadGdiImage(L"camel_cannon", L"../Resources/Camel/Gun.bmp");

		// NPC
		LoadGdiImage(L"prisoner_bind_l", L"../Resources/NPC/L_bind.bmp");
		LoadGdiImage(L"prisoner_bind_r", L"../Resources/NPC/R_bind.bmp");
		LoadGdiImage(L"prisoner_undo_l", L"../Resources/NPC/L_undo.bmp");
		LoadGdiImage(L"prisoner_undo_r", L"../Resources/NPC/R_undo.bmp");
		LoadGdiImage(L"prisoner_run_l", L"../Resources/NPC/L_run.bmp");
		LoadGdiImage(L"prisoner_run_r", L"../Resources/NPC/R_run.bmp");
		LoadGdiImage(L"prisoner_item_l", L"../Resources/NPC/L_item.bmp");
		LoadGdiImage(L"prisoner_item_r", L"../Resources/NPC/R_item.bmp");
		LoadGdiImage(L"prisoner_bye_l", L"../Resources/NPC/L_bye.bmp");
		LoadGdiImage(L"prisoner_bye_r", L"../Resources/NPC/R_bye.bmp");
		LoadGdiImage(L"prisoner_runout_l", L"../Resources/NPC/L_runout.bmp");
		LoadGdiImage(L"prisoner_runout_r", L"../Resources/NPC/R_runout.bmp");
		LoadGdiImage(L"prisoner_fly_l", L"../Resources/NPC/L_fly.bmp");
		LoadGdiImage(L"prisoner_fly_r", L"../Resources/NPC/R_fly.bmp");

		// bullet
		LoadGdiImage(L"pistol_bullet", L"../Resources/Weapon/Pistol/Pistol.bmp");
		LoadGdiImage(L"machinegun_bullet", L"../Resources/Weapon/HeavyMachine/Heavy.bmp");
		LoadGdiImage(L"bomb_bullet", L"../Resources/Weapon/Bomb/Bomb.bmp");
		LoadGdiImage(L"soldier_bomb_bullet", L"../Resources/MonsterBullet/Boom_Bullet.bmp");
		LoadGdiImage(L"tank_bullet_l", L"../Resources/MonsterBullet/left/tank_bullet.bmp");
		LoadGdiImage(L"tank_bullet_r", L"../Resources/MonsterBullet/right/tank_bullet.bmp");
		LoadGdiImage(L"toma_bullet", L"../Resources/Weapon/All/toma_bullet.bmp");
		LoadGdiImage(L"saru_bullet", L"../Resources/Weapon/All/saru_bullet.bmp");
		LoadGdiImage(L"camel_cannon_bullet", L"../Resources/Weapon/HeavyMachine/Heavy2.bmp");
		
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

		// item
		LoadGdiImage(L"item_bomb", L"../Resources/Item/Bomb.bmp");
		LoadGdiImage(L"item_weapon", L"../Resources/Item/item_wapon.bmp");

		// ui
		LoadGdiImage(L"press_start", L"../Resources/UI/PressStart.bmp");
		LoadGdiImage(L"life_bullet", L"../Resources/UI/Life_Bullet.bmp");
		LoadGdiImage(L"big_numbers", L"../Resources/UI/Time.bmp");
		LoadGdiImage(L"small_numbers", L"../Resources/UI/Number.bmp");
		LoadGdiImage(L"infinite", L"../Resources/UI/Infinit.bmp");
	case SCENE_STAGE:
		LoadGdiImage(L"fade", L"../Resources/FadeBuffer.bmp");
		// back
		LoadGdiImage(L"back", L"../Resources/Stage/stage.bmp");
		LoadGdiImage(L"back_collider", L"../Resources/Stage/stage_collider.bmp");
		LoadGdiImage(L"y_sort_1", L"../Resources/Stage/Y_Sort_1.bmp");
		LoadGdiImage(L"y_sort_2", L"../Resources/Stage/Y_Sort_2.bmp");
		LoadGdiImage(L"deco_boss", L"../Resources/Stage/Deco_Boss.bmp");
		LoadGdiImage(L"deco_boss_1", L"../Resources/Stage/Deco_Boss_1.bmp");
		LoadGdiImage(L"deco_boss_2", L"../Resources/Stage/Deco_Boss_2.bmp");
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
			//boss
			LoadGdiImage(L"boss_body_idle", L"../Resources/Monster/Boss/body.bmp");
			LoadGdiImage(L"boss_body_hit", L"../Resources/Monster/Boss/body_hit.bmp");
			LoadGdiImage(L"boss_body_destroy", L"../Resources/Monster/Boss/destroy.bmp");
			LoadGdiImage(L"boss_wing_fire_prepare", L"../Resources/Monster/Boss/fire_preparing.bmp");
			LoadGdiImage(L"boss_wing_fire_att", L"../Resources/Monster/Boss/fire_attack.bmp");
			LoadGdiImage(L"boss_wing_fire_end", L"../Resources/Monster/Boss/fire_end.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_r", L"../Resources/Monster/Boss/right_fire_stand.bmp");
			LoadGdiImage(L"boss_wing_fire_idle_l", L"../Resources/Monster/Boss/left_fire_stand.bmp");
			LoadGdiImage(L"boss_smog_att", L"../Resources/Monster/Boss/smog_attack.bmp");
			LoadGdiImage(L"boss_smog_end", L"../Resources/Monster/Boss/smog_end.bmp");
			LoadGdiImage(L"boss_smog_prepare", L"../Resources/Monster/Boss/smog_preparing.bmp");
			LoadGdiImage(L"boss_smog_stand", L"../Resources/Monster/Boss/smog_stand.bmp");

			LoadGdiImage(L"boss_boost_l", L"../Resources/Monster/Boss/Left/boost_stand.bmp");
			LoadGdiImage(L"boss_boost_r", L"../Resources/Monster/Boss/Right/boost_stand.bmp");
			LoadGdiImage(L"boss_pro_att_l", L"../Resources/Monster/Boss/Left/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_att_r", L"../Resources/Monster/Boss/Right/pro_attack.bmp");
			LoadGdiImage(L"boss_pro_idle_l", L"../Resources/Monster/Boss/Left/pro_stand.bmp");
			LoadGdiImage(L"boss_pro_idle_r", L"../Resources/Monster/Boss/Right/pro_stand.bmp");
		}

		LoadGdiImage(L"camel_rest", L"../Resources/Camel/Idle_Not_Ride.bmp");
		LoadGdiImage(L"camel_run", L"../Resources/Camel/Run.bmp");
		LoadGdiImage(L"camel_idle", L"../Resources/Camel/Idle.bmp");
		LoadGdiImage(L"player_ride", L"../Resources/Player/Ride.bmp");
		LoadGdiImage(L"camel_cannon", L"../Resources/Camel/Gun.bmp");

		// NPC
		LoadGdiImage(L"prisoner_bind_l", L"../Resources/NPC/L_bind.bmp");
		LoadGdiImage(L"prisoner_bind_r", L"../Resources/NPC/R_bind.bmp");
		LoadGdiImage(L"prisoner_undo_l", L"../Resources/NPC/L_undo.bmp");
		LoadGdiImage(L"prisoner_undo_r", L"../Resources/NPC/R_undo.bmp");
		LoadGdiImage(L"prisoner_run_l", L"../Resources/NPC/L_run.bmp");
		LoadGdiImage(L"prisoner_run_r", L"../Resources/NPC/R_run.bmp");
		LoadGdiImage(L"prisoner_item_l", L"../Resources/NPC/L_item.bmp");
		LoadGdiImage(L"prisoner_item_r", L"../Resources/NPC/R_item.bmp");
		LoadGdiImage(L"prisoner_bye_l", L"../Resources/NPC/L_bye.bmp");
		LoadGdiImage(L"prisoner_bye_r", L"../Resources/NPC/R_bye.bmp");
		LoadGdiImage(L"prisoner_runout_l", L"../Resources/NPC/L_runout.bmp");
		LoadGdiImage(L"prisoner_runout_r", L"../Resources/NPC/R_runout.bmp");
		LoadGdiImage(L"prisoner_fly_l", L"../Resources/NPC/L_fly.bmp");
		LoadGdiImage(L"prisoner_fly_r", L"../Resources/NPC/R_fly.bmp");

		// bullet
		LoadGdiImage(L"pistol_bullet", L"../Resources/Weapon/Pistol/Pistol.bmp");
		LoadGdiImage(L"machinegun_bullet", L"../Resources/Weapon/HeavyMachine/Heavy.bmp");
		LoadGdiImage(L"bomb_bullet", L"../Resources/Weapon/Bomb/Bomb.bmp");
		LoadGdiImage(L"soldier_bomb_bullet", L"../Resources/MonsterBullet/Boom_Bullet.bmp");
		LoadGdiImage(L"tank_bullet_l", L"../Resources/MonsterBullet/left/tank_bullet.bmp");
		LoadGdiImage(L"tank_bullet_r", L"../Resources/MonsterBullet/right/tank_bullet.bmp");
		LoadGdiImage(L"toma_bullet", L"../Resources/Weapon/All/toma_bullet.bmp");
		LoadGdiImage(L"saru_bullet", L"../Resources/Weapon/All/saru_bullet.bmp");
		LoadGdiImage(L"camel_cannon_bullet", L"../Resources/Weapon/HeavyMachine/Heavy2.bmp");

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

		// item
		LoadGdiImage(L"item_bomb", L"../Resources/Item/Bomb.bmp");
		LoadGdiImage(L"item_weapon", L"../Resources/Item/item_wapon.bmp");

		// ui
		LoadGdiImage(L"press_start", L"../Resources/UI/PressStart.bmp");
		LoadGdiImage(L"life_bullet", L"../Resources/UI/Life_Bullet.bmp");
		LoadGdiImage(L"big_numbers", L"../Resources/UI/Time.bmp");
		LoadGdiImage(L"small_numbers", L"../Resources/UI/Number.bmp");
		LoadGdiImage(L"infinite", L"../Resources/UI/Infinit.bmp");
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
