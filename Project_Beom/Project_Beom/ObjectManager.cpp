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
	if (nullptr == Obj)
		return;

	wstring* tag = new wstring;
	*tag = L"NoName" + to_wstring(g_Count);
	++g_Count;
	// 나중에 프로그램 종료시 한꺼번에 지워주기 위해
	m_vecNoNames.emplace_back(tag);

	Obj->SetObjectType(ObjType);
	
	m_mapObj[ObjType].insert(MAPOBJ::value_type(tag->c_str(), Obj));
}

void ObjectManager::Update(const float& TimeDelta)
{
	// Collision	
	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_MONSTER_BULLET]);
	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_SLUG]);
	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_MONSTER]);
	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_ITEM]);

	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_MONSTER], &m_mapObj[OBJ_PLAYER_BULLET]);

	GET_MANAGER<CollisionManager>()->CollisionRect(&m_mapObj[OBJ_BLOCK], &m_mapObj[OBJ_PLAYER_BULLET]);

	GET_MANAGER<CollisionManager>()->CollisionRectEx(&m_mapObj[OBJ_PLAYER], &m_mapObj[OBJ_BLOCK]);
	GET_MANAGER<CollisionManager>()->CollisionRectEx(&m_mapObj[OBJ_MONSTER], &m_mapObj[OBJ_BLOCK]);

	// 지형
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_MONSTER]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_PLAYER]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_PLAYER_BULLET]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_MONSTER_BULLET]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_BLOCK]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_SLUG]);
	GET_MANAGER<CollisionManager>()->CollisionPixelToRectDir(&m_mapObj[OBJ_BACK], &m_mapObj[OBJ_ITEM]);

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
			// 사라지지 않는 객체는 죽더라도 지우지 않는다.
			if ((*iter).second->GetDeadCheck() && 
				!(*iter).second->GetNotDeadCheck())
			{
				SAFE_RELEASE((*iter).second);
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
	/*sort(m_vecRender[RENDER_OBJ].begin(), m_vecRender[RENDER_OBJ].end(),
		[](GameObject* a, GameObject* b) { return a->GetInfo().Pos_Y > b->GetInfo().Pos_Y; });*/

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

	// 동적할당을 통해 tag를 설정하였으면 그것들을 해제한다.
	for (auto iter : m_vecNoNames)
	{
		SAFE_DELETE(iter);
	}
	m_vecNoNames.clear();
}

void ObjectManager::ReleaseFromType(OBJTYPE ObjType)
{
	for (auto& obj : m_mapObj[ObjType])
	{
		if (nullptr != obj.second)
		{
			SAFE_RELEASE(obj.second);
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
		SAFE_RELEASE(iter->second);
	}

	m_mapObj[ObjType].erase(iter);
}

void ObjectManager::ReleaseObj(GameObject* Obj, OBJTYPE ObjType)
{
	ReleaseObjFromTag(GetTagFromObj(Obj, ObjType), ObjType);
}

bool ObjectManager::CullingCheck(GameObject* Obj)
{
	if (Obj->GetNoScrollCheck())
		return false;

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
