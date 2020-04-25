#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
	m_CamManager = GET_MANAGER<CameraManager>();
	m_ObjManager = GET_MANAGER<ObjectManager>();
}

Scene::~Scene()
{
	Release();
}

int Scene::Update(const float& TimeDelta)
{
	
	m_ObjManager->Update(TimeDelta);
	m_CamManager->Update(TimeDelta);
	
	return 0;
}

void Scene::Render(HDC hDC)
{
	m_ObjManager->Render(hDC);
}

void Scene::Release()
{
	m_ObjManager->DestroyInstance();
	m_CamManager->DestroyInstance();
}
