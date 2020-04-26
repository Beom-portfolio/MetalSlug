#include "pch.h"
#include "SaruExplosion.h"

SaruExplosion::SaruExplosion()
{
}

SaruExplosion::~SaruExplosion()
{
}

bool SaruExplosion::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"bigexplode.mp3", CH_EFFECT);
	m_Info = GAMEOBJINFO{ 0, 0, 135, 310 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"effect_saru_explosion";
	m_SpriteInfo.MaxFrame = 23;
	m_SpriteInfo.Speed = 35.f;
	return true;
}

int SaruExplosion::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SaruExplosion::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	// for test
	if (m_isCollideOn && true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void SaruExplosion::Release()
{
}
