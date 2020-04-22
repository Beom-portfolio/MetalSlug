#include "pch.h"
#include "SpriteDeco.h"

SpriteDeco::SpriteDeco()
{
}

SpriteDeco::~SpriteDeco()
{
}

bool SpriteDeco::Initialize()
{
	return true;
}

int SpriteDeco::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SpriteDeco::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 0, 248));
}

void SpriteDeco::Release()
{
}
