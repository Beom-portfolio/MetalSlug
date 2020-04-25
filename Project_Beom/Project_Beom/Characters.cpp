#include "pch.h"
#include "Characters.h"

Characters::Characters()
{
}

Characters::~Characters()
{
}

bool Characters::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 174, 324 };
	return true;
}

int Characters::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Characters::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, SRCCOPY);
}

void Characters::Release()
{
}
