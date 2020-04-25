#include "pch.h"
#include "SaruChip.h"

SaruChip::SaruChip()
{
}

SaruChip::~SaruChip()
{
}

bool SaruChip::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 100, 100 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_PLAYER;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"saru_chip";
	m_SpriteInfo.SpriteIndex = float(rand() % 8);
	m_Direction = rand() % 2 ? DIR_RIGHT : DIR_LEFT;
	m_Speed = float(rand() % 400);

	m_GravitySpeed = -float(rand() % 400);
	return true;
}

int SaruChip::Update(const float& TimeDelta)
{
	if (m_fallCheck)
	{
		m_GravityTime += TimeDelta;
		m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
		m_Info.Pos_Y += m_GravitySpeed * TimeDelta;

		if (DIR_RIGHT == m_Direction)
			m_Info.Pos_X += m_Speed * TimeDelta;
		if (DIR_LEFT == m_Direction)
			m_Info.Pos_X -= m_Speed * TimeDelta;

		m_TimeStack = 0;
	}
	else
	{
		m_renderCheck ? m_renderCheck = false : m_renderCheck = true;
		if (m_TimeStack > 0.5f)
			m_isDead = true;
	}
	

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SaruChip::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void SaruChip::Release()
{
}

void SaruChip::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (0 != dir)
	{
		SetFall(false);
	}
}
