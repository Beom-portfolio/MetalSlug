#include "pch.h"
#include "PlayerTop.h"
#include "PlayerTopStandState.h"

PlayerTop::PlayerTop()
{
}

PlayerTop::~PlayerTop()
{
}

bool PlayerTop::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 400, 267 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 0, 0 };

	m_State = new PlayerTopStandState;
	m_State->Enter(this);

	return true;
}

int PlayerTop::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	HandleInput();

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void PlayerTop::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(75, 169, 218));
}

void PlayerTop::Release()
{
	SAFE_DELETE(m_State);
}

void PlayerTop::HandleInput()
{
	State* state = m_State->HandleInput(this, GETMGR(KeyManager));
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}