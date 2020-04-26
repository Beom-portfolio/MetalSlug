#include "pch.h"
#include "MachinegunEffect.h"

MachinegunEffect::MachinegunEffect()
{
}

MachinegunEffect::~MachinegunEffect()
{
}

void MachinegunEffect::SetDirection(DIRECTION dir)
{
	m_Direction = dir;
	switch (m_Direction)
	{
	case DIR_LEFT:
		m_Info.Size_X = 300; m_Info.Size_Y = 75;
		m_SpriteInfo.key = L"effect_machinegun_left";
		break;
	case DIR_RIGHT:
		m_Info.Size_X = 300;  m_Info.Size_Y = 75;
		m_SpriteInfo.key = L"effect_machinegun_right";
		break;
	case DIR_TOP:
		m_Info.Size_X = 75;  m_Info.Size_Y = 300;
		m_SpriteInfo.key = L"effect_machinegun_up";
		break;
	case DIR_BOTTOM:
		m_Info.Size_X = 75;  m_Info.Size_Y = 300;
		m_SpriteInfo.key = L"effect_machinegun_down";
		break;
	}
}

bool MachinegunEffect::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"hit2.wav", CH_EFFECT);
	m_Info = GAMEOBJINFO{ 0, 0, 75, 300 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };
	m_ObjType = OBJ_EFFECT;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"effect_machinegun_down";
	m_SpriteInfo.MaxFrame = 10;
	m_SpriteInfo.Speed = 35.f;

	return true;
}

int MachinegunEffect::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void MachinegunEffect::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if ((DIR_BOTTOM | DIR_TOP) & m_Direction)
	{
		TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
			hMemDC,
			(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
			m_SpriteInfo.StateIndex * m_Info.Size_Y,
			m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
	}
	else 
	{
		TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
			hMemDC,
			0 * m_Info.Size_X,
			(int)m_SpriteInfo.SpriteIndex * m_Info.Size_Y,
			m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
	}
}

void MachinegunEffect::Release()
{
}
