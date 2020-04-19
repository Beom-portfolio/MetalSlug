#include "pch.h"
#include "TestScene.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "GdiManager.h"
#include "CameraManager.h"
#include "Player.h"
#include "Background.h"
#include "PistolBullet.h"
#include "Monster.h"
#include "Soldier.h"
#include "Tank.h"
#include "Toma.h"
#include "Sarubia.h"
#include "Camel.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Initialize()
{
	GameObject* player = AbstractFactory<Player>::CreateObj();
	m_CamManager->SetTarget(player);
	m_CamManager->SetResolution(4200, 600);
	m_CamManager->SetOffset(10, 10, 10, 10);
	m_CamManager->SetFixPos(300, 300);

	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_TEST);
	m_ObjManager->AddObject(L"Player", player, OBJ_PLAYER);
	m_ObjManager->AddObject(L"Camel", AbstractFactory<Camel>::CreateObj(1000, 300), OBJ_SLUG);
	m_ObjManager->AddObject(L"Background", AbstractFactory<Background>::CreateObj(), OBJ_BACK);
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
		m_ObjManager->AddObject(AbstractFactory<Sarubia>::CreateObj(1000 + rand() % 500 - rand() % 100, 300), OBJ_BLOCK);
		//m_ObjManager->AddObject(L"Monster", AbstractFactory<Soldier>::CreateObj(500 + rand() % 100 - rand() % 100, 300), OBJ_MONSTER);
		//m_ObjManager->AddObject(AbstractFactory<Tank>::CreateObj(1000 + rand() % 500 - rand() % 100, 300), OBJ_BLOCK);
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F4))
	{
		m_ObjManager->AddObject(AbstractFactory<Soldier>::CreateObj(500 + rand() % 100 - rand() % 100, 300), OBJ_MONSTER);
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
