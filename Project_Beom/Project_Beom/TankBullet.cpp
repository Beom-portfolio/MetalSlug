#include "pch.h"
#include "TankBullet.h"

TankBullet::TankBullet()
{
}

TankBullet::~TankBullet()
{
}

bool TankBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"TankAtt.wav", CH_EFFECT);
	m_Info = GAMEOBJINFO{ 0, 0, 200, 200 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 60, 50 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"tank_bullet_r";
	else
		m_SpriteInfo.key = L"tank_bullet_l";
	m_SpriteInfo.MaxFrame = 4;
	m_SpriteInfo.Speed = 20.f;

	m_Speed = 600.f;

	return true;
}

int TankBullet::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if (DIR_RIGHT == m_Direction)
	{
		m_SpriteInfo.key = L"tank_bullet_r";
		m_Info.Pos_X += m_Speed * TimeDelta;
	}
	else
	{
		m_SpriteInfo.key = L"tank_bullet_l";
		m_Info.Pos_X -= m_Speed * TimeDelta;
	}

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void TankBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void TankBullet::Release()
{
}
