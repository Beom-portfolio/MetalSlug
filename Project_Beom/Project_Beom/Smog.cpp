#include "pch.h"
#include "Smog.h"

Smog::Smog()
{
}

Smog::~Smog()
{
}

void Smog::SetState(DWORD state)
{
	switch (state)
	{
	case BOSS_IDLE:
		m_SpriteInfo.key = L"boss_smog_stand";
		m_SpriteInfo.MaxFrame = 6;
		m_SpriteInfo.Speed = 20.f;
		break;
	case BOSS_PREPARE:
		m_SpriteInfo.key = L"boss_smog_prepare";
		m_SpriteInfo.MaxFrame = 6;
		m_SpriteInfo.Speed = 20.f;
		break;
	case BOSS_ATT:
		m_SpriteInfo.key = L"boss_smog_att";
		m_SpriteInfo.MaxFrame = 6;
		m_SpriteInfo.Speed = 20.f;
		break;
	case BOSS_ATT_END:
		m_SpriteInfo.key = L"boss_smog_end";
		m_SpriteInfo.MaxFrame = 4;
		m_SpriteInfo.Speed = 20.f;
		break;
	}

	m_SpriteInfo.SpriteIndex = 0.f;
}

bool Smog::Initialize()
{
	m_Info = { 0, 0, 300, 1200 };
	m_SpriteInfo.key = L"boss_smog_stand";
	m_SpriteInfo.MaxFrame = 6;
	m_SpriteInfo.Speed = 20.f;

	return false;
}

int Smog::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	GameObject::Update(TimeDelta);

	return 0;
}

void Smog::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void Smog::Release()
{
}
