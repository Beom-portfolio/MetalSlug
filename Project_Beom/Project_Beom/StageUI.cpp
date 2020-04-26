#include "pch.h"
#include "StageUI.h"

StageUI::StageUI()
{
}

StageUI::~StageUI()
{
}

bool StageUI::Initialize()
{
	m_isNoScroll = true;
	m_isNotDead = true;
	m_RenderType = RENDER_UI;
	return true;
}

int StageUI::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void StageUI::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 255, 0));
}

void StageUI::Release()
{
}
