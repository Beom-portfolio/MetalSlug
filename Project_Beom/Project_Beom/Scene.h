#pragma once
class CameraManager;
class ObjectManager;
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual bool Initialize() PURE;
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

protected:
	CameraManager* m_CamManager = nullptr;
	ObjectManager* m_ObjManager = nullptr;
	SCENESTATE		m_curScene = SCENE_END;
};


