#include "pch.h"
#include "SelectUI.h"

SelectUI::SelectUI()
{
}

SelectUI::~SelectUI()
{
}

bool SelectUI::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 72, 50 };
	m_SpriteInfo.key = L"ui";
	m_SpriteInfo.Speed = 5.f;
	m_SpriteInfo.MaxFrame = 2;
	m_RenderType = RENDER_UI;
	return true;
}

int SelectUI::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SelectUI::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void SelectUI::Release()
{
}
