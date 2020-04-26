#include "pch.h"
#include "Fade.h"

Fade::Fade()
{
}

Fade::~Fade()
{
}

bool Fade::Initialize()
{
	m_Info = GAMEOBJINFO{ WINSIZE_X / 2, WINSIZE_Y / 2, 800, 600 };
	m_isNoScroll = true;
	m_RenderType = RENDER_UI;
	m_Speed = 200;
	return true;
}

int Fade::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	if (true == m_FadeInCheck)
	{
		m_Alpha += m_Speed * TimeDelta;

		if (m_Alpha >= 255.f)
		{
			m_WaitAcc += TimeDelta;
			m_Alpha = 255.f;

			if (1.f <= m_WaitAcc)
			{
				m_ChangeCheck = true;
				return 0;			
			}
		}
	}
	else
	{
		m_Alpha -= m_Speed / 2.f * TimeDelta;

		if (m_Alpha <= 0.f)
			m_Alpha = 0.f;
	}

	return 0;
}

void Fade::Render(HDC hdc)
{
	if (0.f == m_Alpha)
		return;

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"fade")->GetGdiImageDefault();

	BLENDFUNCTION	_bf;
	_bf.SourceConstantAlpha = (int)m_Alpha; // ≈ı∏Ìµµ
	_bf.AlphaFormat = AC_SRC_OVER;
	_bf.BlendOp = 0;
	_bf.BlendFlags = 0;

	GdiAlphaBlend(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, 0, 0, m_Info.Size_X, m_Info.Size_Y, _bf);
}

void Fade::Release()
{
}
