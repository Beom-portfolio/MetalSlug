#include "pch.h"
#include "StaticDeco.h"

StaticDeco::StaticDeco()
{
}

StaticDeco::~StaticDeco()
{
}

bool StaticDeco::Initialize()
{
	return true;
}

int StaticDeco::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void StaticDeco::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		0, 0, m_Info.Size_X, m_Info.Size_Y, RGB(248, 0, 248));
}

void StaticDeco::Release()
{
}
