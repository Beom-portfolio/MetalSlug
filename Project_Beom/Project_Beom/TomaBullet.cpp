#include "pch.h"
#include "TomaBullet.h"
#include "GranadeExplosion.h"

TomaBullet::TomaBullet()
	: GameObject()
{
}

TomaBullet::~TomaBullet()
{
}

bool TomaBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"TomaAtt.mp3", CH_EFFECT);
	m_Info = GAMEOBJINFO{ 0, 0, 100, 100 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 20, 40 };
	m_ObjType = OBJ_MONSTER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"toma_bullet";

	//m_Speed = 1200.f;

	return true;
}

int TomaBullet::Update(const float& TimeDelta)
{
	if (m_cullingCheck)
		m_isDead = true;

	if (m_fallCheck)
	{
		m_GravityTime += TimeDelta;
		m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
		m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void TomaBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void TomaBullet::Release()
{
}

void TomaBullet::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor && 0 != dir)
	{
		GETMGR(ObjectManager)->AddObject(
			AbstractFactory<GranadeExplosion>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y - 80), OBJ_EFFECT);
		m_isDead = true;
	}
}

void TomaBullet::CollisionActivate(GameObject* collideTarget)
{
	GETMGR(ObjectManager)->AddObject(
		AbstractFactory<GranadeExplosion>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y - 80), OBJ_EFFECT);
	m_isDead = true;
}
