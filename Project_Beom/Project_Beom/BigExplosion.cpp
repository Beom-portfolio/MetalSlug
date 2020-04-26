#include "pch.h"
#include "BigExplosion.h"

BigExplosion::BigExplosion()
{
}

BigExplosion::~BigExplosion()
{
}

bool BigExplosion::Initialize()
{
	if (!m_check)
		GETMGR(SoundManager)->PlaySound(L"Explode5.wav", CH_MONSTER);
	m_Info = GAMEOBJINFO{ 0, 0, 170, 170 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"effect_big_explosion";
	m_SpriteInfo.MaxFrame = 20;
	m_SpriteInfo.Speed = 25.f;

	return true;
}

int BigExplosion::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void BigExplosion::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void BigExplosion::Release()
{
}
