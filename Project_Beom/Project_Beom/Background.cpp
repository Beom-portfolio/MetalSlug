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
	m_Info = GAMEOBJINFO{ 9700 / 2, 600 / 2, 9700, 600 };
	m_ObjType = OBJ_BACK;
	m_RenderType = RENDER_BACKGROUND;

	vector<PIXEL24> collPixelInfos;
	collPixelInfos.push_back(PIXEL24{ 0, 0, 248 });
	collPixelInfos.push_back(PIXEL24{ 248, 0, 248 });
	LoadPixelCollider("../Resources/Stage/stage_collider.bmp", collPixelInfos);

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

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, SRCCOPY);
}

void Background::Release()
{
}
