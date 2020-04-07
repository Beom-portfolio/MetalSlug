#include "pch.h"
#include "TestScene.h"
#include "AbstractFactory.h"
#include "ObjectManager.h"
#include "GdiManager.h"
#include "CameraManager.h"
#include "Player.h"
#include "Background.h"

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
	m_CamManager->SetResolution(4294, 606);
	m_CamManager->SetOffset(50, 500, 50, 500);

	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_TEST);
	m_ObjManager->AddObject(L"Player", player, OBJ_PLAYER);
	m_ObjManager->AddObject(L"Background", AbstractFactory<Background>::CreateObj(), OBJ_BACK);
	return true;
}

int TestScene::Update(const float& TimeDelta)
{
	Scene::Update(TimeDelta);

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
