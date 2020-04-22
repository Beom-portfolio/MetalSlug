#include "pch.h"
#include "TestScene.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "GdiManager.h"
#include "CameraManager.h"
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

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Initialize()
{
	GameObject* player = AbstractFactory<Player>::CreateObj();
	player->SetPosition(9400, 200);
	m_CamManager->SetTarget(player);
	m_CamManager->SetResolution(9700, 600);
	m_CamManager->SetOffset(5, 5, 5, 5);
	m_CamManager->SetFixPos(400, 600);

	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_TEST);
	m_ObjManager->AddObject(L"Player", player, OBJ_PLAYER);
	//
	m_ObjManager->AddObject(L"CamelCannon", AbstractFactory<CamelCannon>::CreateObj(), OBJ_AFTERPLAYER);
	m_ObjManager->AddObject(L"Camel", AbstractFactory<Camel>::CreateObj(9300, 300), OBJ_SLUG);

	{
		//map
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

	m_ObjManager->AddObject(L"Boss", AbstractFactory<Boss>::CreateObj(9250, -150), OBJ_MONSTER);
	//m_ObjManager->AddObject(L"Monster", AbstractFactory<Sarubia>::CreateObj(1000, 300), OBJ_BLOCK);
	//m_ObjManager->AddObject(L"Monster", AbstractFactory<Toma>::CreateObj(1000, 200), OBJ_MONSTER);
	//m_ObjManager->AddObject(L"Monster", AbstractFactory<Tank>::CreateObj(1000, 300), OBJ_BLOCK);
	//m_ObjManager->AddObject(L"Monster", AbstractFactory<Monster>::CreateObj(500, 300), OBJ_MONSTER);
	return true;
}

int TestScene::Update(const float& TimeDelta)
{
	Scene::Update(TimeDelta);

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F1))
	{
		GET_MANAGER<CollisionManager>()->GetRenderCheck() ? 
			GET_MANAGER<CollisionManager>()->SetRenderCheck(false) 
			: GET_MANAGER<CollisionManager>()->SetRenderCheck(true);
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F3))
	{
		m_ObjManager->AddObject(L"Boss", AbstractFactory<Boss>::CreateObj(9250, -150), OBJ_MONSTER);
		//m_CamManager->SetFixPos(400, 200);

		//m_ObjManager->AddObject(AbstractFactory<Sarubia>::CreateObj(1000 + rand() % 500 - rand() % 100, 300), OBJ_BLOCK);
		//m_ObjManager->AddObject(L"Monster", AbstractFactory<Soldier>::CreateObj(500 + rand() % 100 - rand() % 100, 300), OBJ_MONSTER);
		//m_ObjManager->AddObject(AbstractFactory<Tank>::CreateObj(1000 + rand() % 500 - rand() % 100, 300), OBJ_BLOCK);
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F4))
	{
		m_CamManager->SetFixPos(400, 600);

		//m_ObjManager->AddObject(AbstractFactory<Soldier>::CreateObj(500 + rand() % 100 - rand() % 100, 300), OBJ_MONSTER);
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F5))
	{
		m_ObjManager->AddObject(AbstractFactory<Tank>::CreateObj(1000 + rand() % 500 - rand() % 100, 300), OBJ_BLOCK);
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F6))
	{
		m_ObjManager->AddObject(AbstractFactory<Toma>::CreateObj(1000, 200), OBJ_MONSTER);
	}

	return 0;
}

void TestScene::Render(HDC hDC)
{
	Scene::Render(hDC);
}

void TestScene::Release()
{
	Scene::Release();
}
