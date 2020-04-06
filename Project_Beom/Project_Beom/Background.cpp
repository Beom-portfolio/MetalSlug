#include "pch.h"
#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

bool Background::Initialize()
{
	m_Info = GAMEOBJINFO{ 5172 / 2, 1685 / 2, 5172, 1685 };
	m_RenderType = RENDER_BACKGROUND;
	m_SpriteInfo.key = L"TestMap";

	return false;
}

int Background::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Background::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 0, 248));
}

void Background::Release()
{
}
