#include "pch.h"
#include "ToolScene.h"
#include "Soldier.h"
#include "Tank.h"
#include "Toma.h"
#include "Sarubia.h"
#include "Background.h"
#include "StaticDeco.h"
#include "SpriteDeco.h"
#include "DummyObject.h"
#include "Prisoner.h"

ToolScene::ToolScene()
	:Scene()
{
}

ToolScene::~ToolScene()
{
}

bool ToolScene::Initialize()
{
	m_CamManager->SetResolution(9700, 600);
	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_TOOL);

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
	m_Dummy = AbstractFactory<DummyObject>::CreateObj();
	GETMGR(ObjectManager)->AddObject(m_Dummy, OBJ_UI);

	return true;
}

int ToolScene::Update(const float& TimeDelta)
{
	m_TimeStack += TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F6))
	{
		GET_MANAGER<CollisionManager>()->GetRenderCheck() ?
			GET_MANAGER<CollisionManager>()->SetRenderCheck(false)
			: GET_MANAGER<CollisionManager>()->SetRenderCheck(true);
	}

	// 카메라 이동
	POSITION camPos = m_CamManager->GetPos();

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'W'))
		camPos.Y += 300.f * TimeDelta;
	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'S'))
		camPos.Y -= 300.f * TimeDelta;
	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'A'))
		camPos.X += 400.f * TimeDelta;
	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'D'))
		camPos.X -= 400.f * TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F1))
		((DummyObject*)m_Dummy)->SetType(MONSTER_SOLDIER);

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F2))
		((DummyObject*)m_Dummy)->SetType(MONSTER_TOMA);

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F3))
		((DummyObject*)m_Dummy)->SetType(MONSTER_TANK);

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F4))
		((DummyObject*)m_Dummy)->SetType(MONSTER_SARU);

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F5))
		((DummyObject*)m_Dummy)->SetType(MONSTER_NPC);

	if (GETMGR(MouseManager)->GetMouseLButtonState(STATE_DOWN))
	{
		POINT mousePos = GETMGR(MouseManager)->GetMousePos();
		POSITION camPos = m_CamManager->GetPos();
		GameObject* monster = nullptr;
		switch (((DummyObject*)m_Dummy)->GetType())
		{
		case MONSTER_SOLDIER: monster = AbstractFactory<Soldier>::CreateObj(); break;
		case MONSTER_TOMA: monster = AbstractFactory<Toma>::CreateObj(); break;
		case MONSTER_TANK: monster = AbstractFactory<Tank>::CreateObj(); break;
		case MONSTER_SARU: monster = AbstractFactory<Sarubia>::CreateObj(); break;
		case MONSTER_NPC: monster = AbstractFactory<Prisoner>::CreateObj(); break;
		}
		monster->SetPosition(mousePos.x - camPos.X, mousePos.y - camPos.Y);
		m_ObjManager->AddObject(monster, OBJ_MONSTER);
		m_vecData.push_back(DataInfo{ monster, ((DummyObject*)m_Dummy)->GetType() });
	}

	if (GETMGR(MouseManager)->GetMouseRButtonState(STATE_DOWN))
	{
		if (!m_vecData.empty())
		{
			vector<DataInfo>::reverse_iterator rIter = m_vecData.rbegin();
			m_ObjManager->ReleaseObj(rIter->Obj, OBJ_MONSTER);
			m_vecData.pop_back();
		}
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F7))
		Save();

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F8))
		Load();

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F9))
	{
		GETMGR(SceneManager)->ChangeSceneState(SCENE_MENU);
		return 0;
	}

	m_CamManager->SetPos(camPos.X, camPos.Y);

	Scene::Update(TimeDelta);
	return 0;
}

void ToolScene::Render(HDC hDC)
{
	Scene::Render(hDC);

	TextOut(hDC, 690, 10, L"몬스터 변경", lstrlen(L"몬스터 변경"));
	TextOut(hDC, 690, 30, L"F1 : 병사", lstrlen(L"F1 : 솔져"));
	TextOut(hDC, 690, 50, L"F2 : 헬기", lstrlen(L"F2 : 헬기"));
	TextOut(hDC, 690, 70, L"F3 : 탱크", lstrlen(L"F3 : 탱크"));
	TextOut(hDC, 690, 90, L"F4 : 사루비아", lstrlen(L"F4 : 사루비아"));
	TextOut(hDC, 690, 110, L"F5 : 죄수", lstrlen(L"F5 : 죄수"));

	TextOut(hDC, 500, 10, L"마우스 좌클릭 : 배치", lstrlen(L"마우스 좌클릭 : 배치"));
	TextOut(hDC, 500, 30, L"마우스 우클릭 : 되돌리기", lstrlen(L"마우스 우클릭 : 되돌리기"));
	TextOut(hDC, 500, 50, L"W,S,A,D : 카메라 이동", lstrlen(L"W,S,A,D : 카메라 이동"));
	TextOut(hDC, 500, 70, L"F6 : 충돌체 보기", lstrlen(L"F6 : 충돌체 보기"));
	TextOut(hDC, 500, 90, L"F7 : 저장", lstrlen(L"F7 : 저장"));
	TextOut(hDC, 500, 110, L"F8 : 불러오기", lstrlen(L"F8 : 불러오기"));
	TextOut(hDC, 500, 130, L"F9 : 되돌아가기", lstrlen(L"F9 : 되돌아가기"));

	

	if (m_SaveCheck)
	{
		if (1.f <= m_TimeStack)
			m_SaveCheck = false;
		TextOut(hDC, 340, 10, L"저장 완료!", lstrlen(L"저장 완료!"));
	}

	if (m_LoadCheck)
	{
		if (1.f <= m_TimeStack)
			m_LoadCheck = false;
		TextOut(hDC, 300, 10, L"불러오기 완료!", lstrlen(L"불러오기 완료!"));
	}
}

void ToolScene::Release()
{
	m_vecData.clear();

	Scene::Release();
}

void ToolScene::Save()
{
	ofstream file;
	file.open(L"../Data/SaveFile.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	if (file.is_open())
	{
		POSITION monPos;
		for (auto data : m_vecData)
		{
			// 몬스터 정보 저장
			monPos = data.Obj->GetPosition();
			file.write((char*)&monPos.X, sizeof(float));
			file.write((char*)&monPos.Y, sizeof(float));
			file.write((char*)&data.type, sizeof(int));
		}
		file.close();

		m_SaveCheck = true;
		m_TimeStack = 0.f;
	}
}

void ToolScene::Load()
{
	ifstream file;
	file.open(L"../Data/SaveFile.dat", ios_base::in | ios_base::binary);
	if(file.is_open())
	{
		m_ObjManager->ReleaseFromType(OBJ_MONSTER);
		m_vecData.clear();

		POSITION monPos;
		MONSTERTYPE monType;
		while (!file.eof())
		{
			file.read((char*)& monPos.X, sizeof(float));
			file.read((char*)& monPos.Y, sizeof(float));
			file.read((char*)& monType, sizeof(int));
		
			GameObject* monster = nullptr;
			switch (monType)
			{
			case MONSTER_SOLDIER: monster = AbstractFactory<Soldier>::CreateObj(); break;
			case MONSTER_TOMA: monster = AbstractFactory<Toma>::CreateObj(); break;
			case MONSTER_TANK: monster = AbstractFactory<Tank>::CreateObj(); break;
			case MONSTER_SARU: monster = AbstractFactory<Sarubia>::CreateObj(); break;
			case MONSTER_NPC: monster = AbstractFactory<Prisoner>::CreateObj(); break;
			}
			monster->SetPosition(monPos.X, monPos.Y);
			m_ObjManager->AddObject(monster, OBJ_MONSTER);
			m_vecData.push_back(DataInfo{ monster, monType });
		}

		m_LoadCheck = true;
		m_TimeStack = 0.f;
	}
}
