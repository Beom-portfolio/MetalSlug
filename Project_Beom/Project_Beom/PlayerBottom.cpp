#include "pch.h"
#include "PlayerBottom.h"
#include "PlayerBottomStandState.h"

PlayerBottom::PlayerBottom()
	: GameObject()
{
}

PlayerBottom::~PlayerBottom()
{
}

bool PlayerBottom::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 400, 267 };

	m_Direction = DIR_RIGHT;
	m_State = new PlayerBottomStandState;
	m_State->Enter(this);
	m_Speed = 1.f;
	return true;
}

int PlayerBottom::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	HandleInput();
	m_isCollide = false;
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void PlayerBottom::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(75, 169, 218));

	// for test
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void PlayerBottom::Release()
{
	SAFE_DELETE(m_State);
}

void PlayerBottom::HandleInput()
{
	State* state = m_State->HandleInput(this, GETMGR(KeyManager));
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}
