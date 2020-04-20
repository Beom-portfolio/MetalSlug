#include "pch.h"
#include "Boss.h"
#include "RightWing.h"
#include "LeftWing.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

bool Boss::Initialize()
{
	m_Info = GAMEOBJINFO{ 600, 170, 900, 450 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };

	m_Speed = 100.f;
	m_RenderType = RENDER_OBJ;

	m_SpriteInfo.key = L"boss_body_idle";
	m_SpriteInfo.Speed = 0.f;
	m_SpriteInfo.SpriteIndex = 0.f;

	m_RightWing = AbstractFactory<RightWing>::CreateObj();
	m_LeftWing = AbstractFactory<LeftWing>::CreateObj();

	return true;
}

int Boss::Update(const float& TimeDelta)
{
	m_RightWing->SetPosition(m_Info.Pos_X + 278.f, m_Info.Pos_Y + 90.f);
	m_RightWing->Update(TimeDelta);
	m_LeftWing->SetPosition(m_Info.Pos_X - 262.f, m_Info.Pos_Y + 90.f);
	m_LeftWing->Update(TimeDelta);

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Boss::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	m_RightWing->Render(hdc);
	m_LeftWing->Render(hdc);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));

	m_RightWing->RenderAfter(hdc);
	m_LeftWing->RenderAfter(hdc);
}

void Boss::Release()
{
	SAFE_RELEASE(m_LeftWing);
	SAFE_RELEASE(m_RightWing);
}
