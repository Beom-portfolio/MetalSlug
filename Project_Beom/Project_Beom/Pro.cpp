#include "pch.h"
#include "Pro.h"

Pro::Pro()
{
}

Pro::~Pro()
{
}

bool Pro::Initialize()
{
	m_Info = { 0, 0, 300, 300 };

	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"boss_pro_idle_r";
	else
		m_SpriteInfo.key = L"boss_pro_idle_l";

	m_SpriteInfo.MaxFrame = 3;
	m_SpriteInfo.Speed = 15.f;


	return true;
}

int Pro::Update(const float& TimeDelta)
{
	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"boss_pro_idle_r";
	else
		m_SpriteInfo.key = L"boss_pro_idle_l";

	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	GameObject::Update(TimeDelta);

	return 0;
}

void Pro::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void Pro::Release()
{
}
