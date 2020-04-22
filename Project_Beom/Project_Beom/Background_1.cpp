#include "pch.h"
#include "Background_1.h"

Background_1::Background_1()
{
}

Background_1::~Background_1()
{
}

bool Background_1::Initialize()
{
	m_Info = GAMEOBJINFO{ 2580 / 2, 350, 2581, 254 };
	m_ObjType = OBJ_BACK_FRONT_2;
	m_RenderType = RENDER_BACKGROUND;

	return true;
}

int Background_1::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Background_1::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"back_1")->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 0, 248));
}

void Background_1::Release()
{
}
