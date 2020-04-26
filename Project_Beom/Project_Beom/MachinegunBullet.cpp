#include "pch.h"
#include "MachinegunBullet.h"
#include "PistolEffect.h"
#include "MediumExplosion.h"
#include "BigExplosion.h"
#include "GranadeExplosion.h"
#include "MachinegunEffect.h"
#include "PistolEffect.h"

MachinegunBullet::MachinegunBullet()
{
}

MachinegunBullet::~MachinegunBullet()
{
}

bool MachinegunBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"MachinegunSound.mp3", CH_PLAYER);
	m_Info = GAMEOBJINFO{ 0, 0, 60, 60 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 20, 20 };
	m_ObjType = OBJ_PLAYER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"machinegun_bullet";

	m_Speed = 1000.f;
	m_Damage = 2;

	return true;
}

int MachinegunBullet::Update(const float& TimeDelta)
{
	if (DIR_RIGHT == m_Direction)
		m_Info.Pos_X += m_Speed * TimeDelta;
	else if (DIR_LEFT == m_Direction)
		m_Info.Pos_X -= m_Speed * TimeDelta;
	else if (DIR_BOTTOM == m_Direction)
		m_Info.Pos_Y += m_Speed * TimeDelta;
	else if (DIR_TOP == m_Direction)
		m_Info.Pos_Y -= m_Speed * TimeDelta;
	else
		GotoAngle(TimeDelta);

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void MachinegunBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	// angle
	// YÃà
	float angle = m_Angle;
	if(angle > 90.f) angle -= (((int)angle / 90) * 90.f);
	int idxX = 0 == ((int)angle / 10) ? 0 : ((int)angle / 10) + 1;
	if (10 == idxX) idxX = 0;
	int idxY = (int)m_Angle / 90;

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		idxX * m_Info.Size_X, idxY * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 0, 0));
}

void MachinegunBullet::Release()
{
}

void MachinegunBullet::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor && 0 != dir)
	{
		GameObject* effect = AbstractFactory<MachinegunEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y);
		if(DIR_LEFT & dir)
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

void MachinegunBullet::CollisionActivate(GameObject* collideTarget)
{
	if (!collideTarget->GetCollideCheck())
	{
		collideTarget->Hit(m_Damage);
		GETMGR(ObjectManager)->AddObject(
			AbstractFactory<PistolEffect>::CreateObj((int)m_Info.Pos_X, (int)m_Info.Pos_Y), OBJ_EFFECT);
		m_isDead = true;
	}
}
