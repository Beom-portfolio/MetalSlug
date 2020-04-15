#include "pch.h"
#include "Blood.h"

Blood::Blood()
{
}

Blood::~Blood()
{
}

bool Blood::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 200, 200 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	if(DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"effect_blood_right";
	else
		m_SpriteInfo.key = L"effect_blood_left";
	m_SpriteInfo.MaxFrame = 8;
	m_SpriteInfo.Speed = 20.f;

	return true;
}

int Blood::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"effect_blood_right";
	else
		m_SpriteInfo.key = L"effect_blood_left";

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Blood::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void Blood::Release()
{
}
