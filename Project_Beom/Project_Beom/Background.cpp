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
	m_Info = GAMEOBJINFO{ 4200 / 2, 600 / 2, 4200, 600 };
	m_ObjType = OBJ_BACK;
	m_RenderType = RENDER_BACKGROUND;

	LoadPixelCollider("../Resources/Stage/Stage_Floor_0_Collider_Info.bmp", 255, 0, 0);

	return true;
}

int Background::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Background::Render(HDC hdc)
{
	HDC hMemDC;

	if(true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"back_collider")->GetGdiImageDefault();
	else
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"back")->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void Background::Release()
{
}
