#include "pch.h"
#include "KnifeBullet.h"

KnifeBullet::KnifeBullet()
{
}

KnifeBullet::~KnifeBullet()
{
}

bool KnifeBullet::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 20, 20 };
	m_ObjType = OBJ_PLAYER_BULLET;
	m_RenderType = RENDER_OBJ;

	return true;
}

int KnifeBullet::Update(const float& TimeDelta)
{
	if (m_TimeStack >= 0.25f)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void KnifeBullet::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void KnifeBullet::Release()
{
}

void KnifeBullet::CollisionActivate(GameObject* collideTarget)
{
}
