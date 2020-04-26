#include "pch.h"
#include "SelectScene.h"
#include "Characters.h"
#include "Slot.h"
#include "SelectUI.h"
#include "SelectScreen.h"

SelectScene::SelectScene()
	:Scene()
{
}

SelectScene::~SelectScene()
{
}

bool SelectScene::Initialize()
{
	GETMGR(GdiManager)->LoadImageBySceneState(SCENE_SELECT);
	GETMGR(SoundManager)->PlayBGM(L"Select.mp3", CH_BGM);

	m_ObjManager->AddObject(AbstractFactory<SelectScreen>::CreateObj(), OBJ_EFFECT);

	SPRITEINFO info;
	ZeroMemory(&info, sizeof(SPRITEINFO));

	m_marco = AbstractFactory<Characters>::CreateObj();
	info.key = L"marco";
	m_marco->SetSpriteInfo(info);
	m_marco->SetPosition(130.f, 325.f);
	m_ObjManager->AddObject(m_marco, OBJ_PLAYER);

	m_eri = AbstractFactory<Characters>::CreateObj();
	info.key = L"eri";
	m_eri->SetSpriteInfo(info);
	m_eri->SetPosition(310.f, 325.f);
	m_ObjManager->AddObject(m_eri, OBJ_PLAYER);

	m_tarma = AbstractFactory<Characters>::CreateObj();
	info.key = L"tarma";
	m_tarma->SetSpriteInfo(info);
	m_tarma->SetPosition(490.f, 325.f);
	m_ObjManager->AddObject(m_tarma, OBJ_PLAYER);

	m_fio = AbstractFactory<Characters>::CreateObj();
	info.key = L"fio";
	m_fio->SetSpriteInfo(info);
	m_fio->SetPosition(670.f, 325.f);
	m_ObjManager->AddObject(m_fio, OBJ_PLAYER);

	m_ObjManager->AddObject(AbstractFactory<Slot>::CreateObj(130, 325), OBJ_AFTERPLAYER);
	m_ObjManager->AddObject(AbstractFactory<Slot>::CreateObj(310, 325), OBJ_AFTERPLAYER);
	m_ObjManager->AddObject(AbstractFactory<Slot>::CreateObj(490, 325), OBJ_AFTERPLAYER);
	m_ObjManager->AddObject(AbstractFactory<Slot>::CreateObj(670, 325), OBJ_AFTERPLAYER);

	return true;
}

int SelectScene::Update(const float& TimeDelta)
{
	m_TimeStack += TimeDelta;

	if (m_endCheck && 4.f <= m_TimeStack)
	{
		GETMGR(SceneManager)->ChangeSceneState(SCENE_STAGE);
		return 0;
	}

	if (!m_endCheck && !m_onceCheck && 1.5f <= m_TimeStack)
	{
		m_ui = AbstractFactory<SelectUI>::CreateObj(130 - 5, 122);
		m_ObjManager->AddObject(m_ui, OBJ_UI);
		m_slotIndex = 0;
		m_onceCheck = true;
	}

	if (m_onceCheck && !m_slectCheck)
	{
		SPRITEINFO info;
		ZeroMemory(&info, sizeof(SPRITEINFO));

		if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_LEFT))
			m_slotIndex -= 1;

		if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_RIGHT))
			m_slotIndex += 1;	

		if (m_slotIndex < 0)
			m_slotIndex = 3;
		else if (m_slotIndex > 3)
			m_slotIndex = 0;

		info.key = L"marco";
		m_marco->SetSpriteInfo(info);
		info.key = L"eri";
		m_eri->SetSpriteInfo(info);
		info.key = L"tarma";
		m_tarma->SetSpriteInfo(info);
		info.key = L"fio";
		m_fio->SetSpriteInfo(info);

		switch (m_slotIndex)
		{
		case 0:
			m_ui->SetPosition(130 - 5, 122);
			info.key = L"marco_select";
			m_marco->SetSpriteInfo(info);
			break;
		case 1:
			m_ui->SetPosition(310 - 5, 122);
			info.key = L"eri_select";
			m_eri->SetSpriteInfo(info);
			break;
		case 2:
			m_ui->SetPosition(490 - 5, 122);
			info.key = L"tarma_select";
			m_tarma->SetSpriteInfo(info);
			break;
		case 3:
			m_ui->SetPosition(670 - 5, 122);
			info.key = L"fio_select";
			m_fio->SetSpriteInfo(info);
			break;
		}

		// 캐릭터 선택시 입력 비활성화 
		if ((2 == m_slotIndex) && GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_RETURN))
		{	
			GETMGR(SoundManager)->PlaySound(L"TarmaSelect.mp3", CH_VOICE);
			info.key = L"tarma_selected";
			m_tarma->SetSpriteInfo(info);
			m_slectCheck = true;
		}
	}

	// 선택시 슬롯 내려옴
	if (!m_endCheck && m_slectCheck)
	{
		SPRITEINFO info;
		ZeroMemory(&info, sizeof(SPRITEINFO));

		GameObject* selectSlot = AbstractFactory<Slot>::CreateObj(490, 0);
		info.key = L"slot_tarma";
		info.MaxFrame = 2;
		info.Speed = 5.f;
		selectSlot->SetSpriteInfo(info);
		selectSlot->SetDirection(DIR_BOTTOM);
		selectSlot->SetSpeed(700.f);
		m_ObjManager->AddObject(selectSlot, OBJ_AFTERPLAYER);
		m_TimeStack = 0.f;
		m_endCheck = true;
	}

	Scene::Update(TimeDelta);

	return 0;
}

void SelectScene::Render(HDC hDC)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"fade")->GetGdiImageDefault();
	BitBlt(hDC, 0, 0, WINSIZE_X, WINSIZE_Y, hMemDC, 0, 0, SRCCOPY);

	Scene::Render(hDC);
}

void SelectScene::Release()
{
	GETMGR(SoundManager)->StopAll();
	Scene::Release();
}
