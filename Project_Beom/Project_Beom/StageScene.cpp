#include "pch.h"
#include "StageScene.h"
#include "Player.h"
#include "Background.h"
#include "PistolBullet.h"
#include "Soldier.h"
#include "Tank.h"
#include "Toma.h"
#include "Sarubia.h"
#include "Camel.h"
#include "CamelCannon.h"
#include "Boss.h"
#include "StaticDeco.h"
#include "SpriteDeco.h"
#include "Prisoner.h"
#include "Item.h"
#include "StageUI.h"
#include "Number.h"
#include "Fade.h"

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

bool StageScene::Initialize()
{
	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_STAGE);
	GETMGR(SoundManager)->PlayBGM(L"Stage.mp3", CH_BGM);
	GETMGR(SoundManager)->PlaySound(L"MissionStart.mp3", CH_VOICE);
	// ui
	{
		m_Fade = AbstractFactory<Fade>::CreateObj();
		m_ObjManager->AddObject(m_Fade, OBJ_UI1);

		SPRITEINFO info;
		ZeroMemory(&info, sizeof(SPRITEINFO));
		GameObject* ui = AbstractFactory<StageUI>::CreateObj();
		info.key = L"press_start";
		ui->SetSize(500, 50);
		ui->SetSpriteInfo(info);
		ui->SetPosition(750, 40);
		m_ObjManager->AddObject(ui, OBJ_UI);

		ui = AbstractFactory<StageUI>::CreateObj();
		info.key = L"life_bullet";
		ui->SetSize(300, 64);
		ui->SetSpriteInfo(info);
		ui->SetPosition(170, 50);
		m_ObjManager->AddObject(ui, OBJ_UI);

		ui = AbstractFactory<Number>::CreateObj();
		((Number*)ui)->SetNumberStyle(NUMSTYLE_BIG);
		((Number*)ui)->SetNumber(0);
		ui->SetPosition(432, 40);
		m_ObjManager->AddObject(L"TimeUI", ui, OBJ_UI);

		ui = AbstractFactory<Number>::CreateObj();
		((Number*)ui)->SetNumberStyle(NUMSTYLE_NOTNUMBER);
		ui->SetSize(40, 16);
		ui->SetPosition(127, 70);
		info.key = L"infinite";
		ui->SetSpriteInfo(info);
		m_ObjManager->AddObject(ui, OBJ_UI);

		ui = AbstractFactory<Number>::CreateObj();
		((Number*)ui)->SetNumberStyle(NUMSTYLE_NOTNUMBER);
		ui->SetSize(40, 16);
		ui->SetPosition(213, 50);
		info.key = L"infinite";
		ui->SetSpriteInfo(info);
		ui->SetRenderCheck(false);
		m_ObjManager->AddObject(L"BulletInfinite", ui, OBJ_UI);

		ui = AbstractFactory<Number>::CreateObj();
		((Number*)ui)->SetNumberStyle(NUMSTYLE_SMALL);
		((Number*)ui)->SetNumber(200);
		ui->SetPosition(230, 50);
		m_ObjManager->AddObject(L"BulletUI", ui, OBJ_UI);

		ui = AbstractFactory<Number>::CreateObj();
		((Number*)ui)->SetNumberStyle(NUMSTYLE_SMALL);
		((Number*)ui)->SetNumber(10);
		ui->SetPosition(292, 50);
		m_ObjManager->AddObject(L"BombUI", ui, OBJ_UI);
	}

	//player
	{
		m_Player = AbstractFactory<Player>::CreateObj();
		m_Player->SetPosition(100, 400);
		m_CamManager->SetTarget(m_Player);
		m_CamManager->SetResolution(9700, 600);
		m_CamManager->SetOffset(5, 5, 5, 100);
		m_CamManager->SetFixPos(200, 100);
		m_ObjManager->AddObject(L"Player", m_Player, OBJ_PLAYER);	
	}
	
	//slug
	m_ObjManager->AddObject(L"CamelCannon", AbstractFactory<CamelCannon>::CreateObj(), OBJ_AFTERPLAYER);
	m_ObjManager->AddObject(L"Camel", AbstractFactory<Camel>::CreateObj(5500, 400), OBJ_SLUG);

	//map
	{
		
		m_ObjManager->AddObject(L"Background", AbstractFactory<Background>::CreateObj(), OBJ_BACK);

		//deco
		GameObject* deco = AbstractFactory<StaticDeco>::CreateObj();
		deco->SetSize(365, 129);
		deco->SetPosition(1930, 250);
		SPRITEINFO info = deco->GetSpriteInfo();
		info.key = L"y_sort_1";
		deco->SetSpriteInfo(info);
		m_ObjManager->AddObject(L"deco_1", deco, OBJ_AFTERPLAYER);

		deco = AbstractFactory<StaticDeco>::CreateObj();
		deco->SetSize(293, 246);
		deco->SetPosition(1668, 430);
		info = deco->GetSpriteInfo();
		info.key = L"y_sort_2";
		deco->SetSpriteInfo(info);
		m_ObjManager->AddObject(L"deco_2", deco, OBJ_AFTERPLAYER);

		deco = AbstractFactory<SpriteDeco>::CreateObj();
		deco->SetSize(773, 529);
		deco->SetPosition(9320, 254);
		info = deco->GetSpriteInfo();
		info.key = L"deco_boss";
		info.MaxFrame = 4;
		info.Speed = 25.f;
		deco->SetSpriteInfo(info);
		m_ObjManager->AddObject(L"deco_3", deco, OBJ_BACK);

		deco = AbstractFactory<SpriteDeco>::CreateObj();
		deco->SetSize(469, 153);
		deco->SetPosition(8918, 270);
		info = deco->GetSpriteInfo();
		info.key = L"deco_boss_1";
		info.MaxFrame = 4;
		info.Speed = 20.f;
		deco->SetSpriteInfo(info);
		m_ObjManager->AddObject(L"deco_4", deco, OBJ_BACK1);

		deco = AbstractFactory<SpriteDeco>::CreateObj();
		deco->SetSize(220, 153);
		deco->SetPosition(9594, 270);
		info = deco->GetSpriteInfo();
		info.key = L"deco_boss_2";
		info.MaxFrame = 4;
		info.Speed = 20.f;
		deco->SetSpriteInfo(info);
		m_ObjManager->AddObject(L"deco_5", deco, OBJ_BACK1);
	}

	// monster
	{
		ifstream file;
		file.open(L"../Data/SaveFile.dat", ios_base::in | ios_base::binary);
		if (file.is_open())
		{
			POSITION monPos;
			MONSTERTYPE monType;
			OBJTYPE objType;
			while (!file.eof())
			{
				file.read((char*)& monPos.X, sizeof(float));
				file.read((char*)& monPos.Y, sizeof(float));
				file.read((char*)& monType, sizeof(int));

				GameObject* monster = nullptr;
				switch (monType)
				{
				case MONSTER_SOLDIER:
					monster = AbstractFactory<Soldier>::CreateObj();
					objType = OBJ_MONSTER;
					break;
				case MONSTER_TOMA:
					monster = AbstractFactory<Toma>::CreateObj();
					objType = OBJ_MONSTER;
					break;
				case MONSTER_TANK:
					monster = AbstractFactory<Tank>::CreateObj();
					objType = OBJ_BLOCK;
					break;
				case MONSTER_SARU:
					monster = AbstractFactory<Sarubia>::CreateObj();
					objType = OBJ_BLOCK;
					break;
				case MONSTER_NPC:
					monster = AbstractFactory<Prisoner>::CreateObj();
					objType = OBJ_MONSTER;
					break;
				}
				monster->SetPosition(monPos.X, monPos.Y);
				m_ObjManager->AddObject(monster, objType);
			}
		}
	}

	return true;
}

int StageScene::Update(const float& TimeDelta)
{
	// 보스 생성
	if (!m_onceCheck && 9300.f <= m_Player->GetPosition().X)
	{
		GETMGR(SoundManager)->PlayBGM(L"Boss.mp3", CH_BGM);
		m_CamManager->SetFixPos(0, 600);
		m_ObjManager->AddObject(L"Boss", AbstractFactory<Boss>::CreateObj(9290, -150), OBJ_MONSTER);
		m_onceCheck = true;
	}

	if (m_onceCheck && nullptr == m_ObjManager->GetObjFromTag(L"Boss", OBJ_MONSTER))
	{	
		m_stack += TimeDelta;
		if (!m_stackCheck)
		{
			if (1.f <= m_stack)
			{
				GETMGR(SoundManager)->StopSound(CH_BGM);
				GETMGR(SoundManager)->PlaySound(L"StageClear.mp3", CH_BGM);
				GETMGR(SoundManager)->PlaySound(L"MissionComplete.mp3", CH_VOICE);
				m_stackCheck = true;
			}
		}
		if (6.f <= m_stack)
		{
			if (((Fade*)m_Fade)->GetChangeCheck())
			{
				GETMGR(SceneManager)->ChangeSceneState(SCENE_CREDIT);
				return 0;
			}
			((Fade*)m_Fade)->SetFade(true);
		}
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F1))
	{
		GET_MANAGER<CollisionManager>()->GetRenderCheck() ?
			GET_MANAGER<CollisionManager>()->SetRenderCheck(false)
			: GET_MANAGER<CollisionManager>()->SetRenderCheck(true);
	}

	Scene::Update(TimeDelta);
	return 0;
}

void StageScene::Render(HDC hDC)
{
	Scene::Render(hDC);
}

void StageScene::Release()
{
	GETMGR(SoundManager)->StopAll();
	Scene::Release();
}
