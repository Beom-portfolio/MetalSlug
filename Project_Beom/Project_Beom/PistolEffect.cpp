#include "pch.h"
#include "PistolEffect.h"

PistolEffect::PistolEffect()
{
}

PistolEffect::~PistolEffect()
{
}

bool PistolEffect::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"hit2.wav", CH_EFFECT);
	m_Info = GAMEOBJINFO{ 0, 0, 32, 32 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"effect_pistol";
	m_SpriteInfo.MaxFrame = 10;
	m_SpriteInfo.Speed = 30.f;

	return true;
}

int PistolEffect::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void PistolEffect::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void PistolEffect::Release()
{
}
