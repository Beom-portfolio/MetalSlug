#include "pch.h"
#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	ReleaseAll();
}

const TCHAR* ObjectManager::GetTagFromObj(GameObject* Obj, OBJTYPE ObjType)
{
	MAPOBJ::iterator iter = find_if(begin(m_mapObj[ObjType]), end(m_mapObj[ObjType]),
		[&](auto& p) {return p.second == Obj; });

	if (end(m_mapObj[ObjType]) == iter)
		return nullptr;

	return iter->first;
}

GameObject* ObjectManager::GetObjFromTag(const TCHAR* tag, OBJTYPE ObjType)
{
	MAPOBJ::iterator iter = find_if(begin(m_mapObj[ObjType]), end(m_mapObj[ObjType]),
		[&](auto& p) {return 0 == wcscmp(p.first, tag); });

	if (m_mapObj[ObjType].end() == iter)
		return nullptr;

	return (iter)->second;
}

void ObjectManager::AddObject(const TCHAR* tag, GameObject* Obj, OBJTYPE ObjType)
{
	if (nullptr == Obj)
		return;

	Obj->SetObjectType(ObjType);

	m_mapObj[ObjType].insert(MAPOBJ::value_type(tag, Obj));
}

void ObjectManager::AddObject(GameObject* Obj, OBJTYPE ObjType)
{
	wstring tag;
	tag = L"NoName_" + to_wstring(g_Count);
	++g_Count;

	if (nullptr == Obj)
		return;

	Obj->SetObjectType(ObjType);

	m_mapObj[ObjType].insert(MAPOBJ::value_type(tag.c_str(), Obj));
}

void ObjectManager::Update(const float& TimeDelta)
{
	// Collision
	//GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_MONSTER]);
	//GET_MANAGER<CollisionManager>()->CollisionRectEx(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_MONSTER]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_PLAYER]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_BULLET]);

	// Culling Check
	POSITION CamPos = GETMGR(CameraManager)->GetPos();
	POSITION ScreenSize = POSITION{ (float)WINSIZE_X, (float)WINSIZE_Y };
	m_outOfScreen.left = LONG(0.f - CamPos.X);
	m_outOfScreen.right = LONG(ScreenSize.X - CamPos.X);
	m_outOfScreen.top = LONG(0.f - CamPos.Y);
	m_outOfScreen.bottom = LONG(ScreenSize.Y - CamPos.Y);

	// Update
	for (auto i = 0; i < OBJ_END; ++i)
	{
		const auto& iter_begin = m_mapObj[i].begin();
		const auto& iter_end = m_mapObj[i].end();

		for (auto iter = iter_begin; iter != iter_end;)
		{
			(*iter).second->SetCulling(CullingCheck((*iter).second));

			// 죽은 상태라면 컨테이너에서 삭제한다.
			if (true == (*iter).second->GetState())
			{
				delete (*iter).second;
				(*iter).second = nullptr;
				iter = m_mapObj[i].erase(iter);
			}
			else
			{
				(*iter).second->Update(TimeDelta);
				++iter;
			}
		}
	}
}

void ObjectManager::Render(HDC hDC)
{
	for (auto i = 0; i < OBJ_END; ++i)
	{
		for (auto& obj : m_mapObj[i])
		{
			RENDERTYPE type = obj.second->GetRenderType();
			m_vecRender[type].emplace_back(obj.second);
		}
	}

	// Y축 기준으로 render 순서 정렬
	sort(m_vecRender[RENDER_OBJ].begin(), m_vecRender[RENDER_OBJ].end(),
		[](GameObject* a, GameObject* b) { return a->GetInfo().Pos_Y > b->GetInfo().Pos_Y; });

	for (auto i = 0; i < RENDER_END; ++i)
	{
		for (auto& obj : m_vecRender[i])
		{
			if (obj->GetRenderCheck() && !obj->GetCullingCheck())
				obj->Render(hDC);
		}
		m_vecRender[i].clear();
	}
}

void ObjectManager::ReleaseAll()
{
	for (auto i = 0; i < OBJ_END; ++i)
	{
		for (auto& obj : m_mapObj[i])
		{
			SAFE_RELEASE(obj.second);
		}
		m_mapObj[i].clear();
	}
}

void ObjectManager::ReleaseFromType(OBJTYPE ObjType)
{
	for (auto& obj : m_mapObj[ObjType])
	{
		if (nullptr != obj.second)
		{
			delete obj.second;
			obj.second = nullptr;
		}
	}
	m_mapObj[ObjType].clear();
}

void ObjectManager::ReleaseObjFromTag(const TCHAR* tag, OBJTYPE ObjType)
{
	MAPOBJ::iterator iter = find_if(begin(m_mapObj[ObjType]), end(m_mapObj[ObjType]),
		[&](auto& p) {return 0 == wcscmp(p.first, tag); });

	if (m_mapObj[ObjType].end() == iter)
		return;

	if (nullptr != iter->second)
	{
		delete iter->second;
		iter->second = nullptr;
	}

	m_mapObj[ObjType].erase(iter);
}

void ObjectManager::ReleaseObj(GameObject* Obj, OBJTYPE ObjType)
{
	ReleaseObjFromTag(GetTagFromObj(Obj, ObjType), ObjType);
}

bool ObjectManager::CullingCheck(GameObject* Obj)
{
	GAMEOBJINFO Info = Obj->GetInfo();
	RECT objRect;
	objRect.left = LONG(Info.Pos_X - (float)Info.Size_X / 2);
	objRect.right = LONG(Info.Pos_X + (float)Info.Size_X / 2);
	objRect.top = LONG(Info.Pos_Y - (float)Info.Size_Y / 2);
	objRect.bottom = LONG(Info.Pos_Y + (float)Info.Size_Y / 2);

	if (objRect.left > m_outOfScreen.right || objRect.right < m_outOfScreen.left)
		return true;
	if (objRect.top > m_outOfScreen.bottom || objRect.bottom < m_outOfScreen.top)
		return true;

	return false;
}
