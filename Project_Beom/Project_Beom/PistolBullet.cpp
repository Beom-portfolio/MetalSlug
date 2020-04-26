#include "pch.h"
#include "PistolBullet.h"
#include "PistolEffect.h"

PistolBullet::PistolBullet()
	: GameObject()
{
}

PistolBullet::~PistolBullet()
{
}

bool PistolBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"Pistol_Fire.mp3", CH_PLAYER);
	m_Info = GAMEOBJINFO{ 0, 0, 20, 20 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 20, 20 };
	m_ObjType = OBJ_PLAYER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"pistol_bullet";

	m_Speed = 1200.f;

	return true;
}

int PistolBullet::Update(const float& TimeDelta)
{
	if (DIR_RIGHT == m_Direction)
		m_Info.Pos_X += m_Speed * TimeDelta;
	if (DIR_LEFT == m_Direction)
		m_Info.Pos_X -= m_Speed * TimeDelta;
	if (DIR_BOTTOM == m_Direction)
		m_Info.Pos_Y += m_Speed * TimeDelta;
	if (DIR_TOP == m_Direction)
		m_Info.Pos_Y -= m_Speed * TimeDelta;

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	m_Damage = 10;
	return 0;
}

void PistolBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
	
	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void PistolBullet::Release()
{
}

void PistolBullet::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor && 0 != dir)
	{
		GETMGR(ObjectManager)->AddObject(
			AbstractFactory<PistolEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y), OBJ_EFFECT);
		m_isDead = true;
	}
}

void PistolBullet::CollisionActivate(GameObject* collideTarget)
{
	if (!collideTarget->GetCollideCheck())
	{
		collideTarget->Hit(m_Damage);
		GETMGR(ObjectManager)->AddObject(
			AbstractFactory<PistolEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y), OBJ_EFFECT);
		m_isDead = true;
	}
}
