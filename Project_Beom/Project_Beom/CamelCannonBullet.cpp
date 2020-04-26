#include "pch.h"
#include "CamelCannonBullet.h"
#include "MachinegunEffect.h"
#include "PistolEffect.h"

CamelCannonBullet::CamelCannonBullet()
{
}

CamelCannonBullet::~CamelCannonBullet()
{
}

bool CamelCannonBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"MachinegunSound.mp3", CH_PLAYER);
	m_Info = GAMEOBJINFO{ 0, 0, 90, 90 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 20, 20 };
	m_ObjType = OBJ_PLAYER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"camel_cannon_bullet";

	m_Speed = 1500.f;
	m_Damage = 3;

	return true;
}

int CamelCannonBullet::Update(const float& TimeDelta)
{
	GotoAngle(TimeDelta);

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void CamelCannonBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	// angle
	// YÃà
	float angle = m_Angle;
	if (angle >= 90.f) angle -= (((int)angle / 90) * 90.f);
	int idxX = 0 == ((int)angle / 10) ? 0 : ((int)angle / 10);
	int idxY = (int)m_Angle / 90;

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		idxX * m_Info.Size_X, idxY * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 0, 0));
}

void CamelCannonBullet::Release()
{
}

void CamelCannonBullet::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor && 0 != dir)
	{
		GETMGR(SoundManager)->PlaySound(L"hit2.wav", CH_EFFECT);
		GameObject* effect = AbstractFactory<MachinegunEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y);
		if (DIR_LEFT & dir)
			effect->SetDirection(DIR_LEFT);
		else if (DIR_RIGHT & dir)
			effect->SetDirection(DIR_RIGHT);
		if (DIR_TOP & dir)
			effect->SetDirection(DIR_TOP);
		else if (DIR_BOTTOM & dir)
			effect->SetDirection(DIR_BOTTOM);
		GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
		m_isDead = true;
	}
}

void CamelCannonBullet::CollisionActivate(GameObject* collideTarget)
{
	if (!collideTarget->GetCollideCheck())
	{
		GETMGR(SoundManager)->PlaySound(L"hit2.wav", CH_EFFECT);
		collideTarget->Hit(m_Damage);
		GETMGR(ObjectManager)->AddObject(
			AbstractFactory<PistolEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y), OBJ_EFFECT);
		m_isDead = true;
	}
}
