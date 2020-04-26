#include "pch.h"
#include "Slot.h"

Slot::Slot()
{
}

Slot::~Slot()
{
}

bool Slot::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 174, 324 };
	m_Speed = 500.f;
	m_Direction = DIR_TOP;
	m_SpriteInfo.key = L"slot";
	return true;
}

int Slot::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	if (m_waitTime >= m_TimeStack)
		return 0;

	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;	

	if (DIR_TOP == m_Direction)
		m_Info.Pos_Y -= m_Speed * TimeDelta;
	else
		m_Info.Pos_Y += m_Speed * TimeDelta;

	if (325.f <= m_Info.Pos_Y)
		m_Info.Pos_Y = 325.f;

	if (m_cullingCheck)
		m_isDead = true;
	

	return 0;
}

void Slot::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void Slot::Release()
{
}
