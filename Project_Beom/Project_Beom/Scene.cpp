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
}