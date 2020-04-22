#include "pch.h"
#include "Background_2.h"

Background_2::Background_2()
{
}

Background_2::~Background_2()
{
}

bool Background_2::Initialize()
{
	m_Info = GAMEOBJINFO{ 9700 / 2, 600 / 2, 9700, 600 };
	m_ObjType = OBJ_BACK_FRONT_2;
	m_RenderType = RENDER_BACKGROUND;

	return true;
}

int Background_2::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Background_2::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"back_2")->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 0, 248));
}

void Background_2::Release()
{
}
