#include "pch.h"
#include "TestScene.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "GdiManager.h"
#include "CameraManager.h"
#include "Player.h"
#include "Background.h"
#include "PistolBullet.h"

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
	m_CamManager->SetOffset(50, 50, 50, 50);

	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_TEST);
	m_ObjManager->AddObject(L"Player", player, OBJ_PLAYER);
	m_ObjManager->AddObject(L"Background", AbstractFactory<Background>::CreateObj(), OBJ_BACK);
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
