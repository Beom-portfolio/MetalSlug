#include "pch.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player()
	: GameObject()
{
}

Player::~Player()
{
}

bool Player::Initialize()
{
	m_Info = GAMEOBJINFO{ 400, 300, 60, 100 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 60, 100 };
	m_Speed = 500.f;
	m_RenderType = RENDER_OBJ;

	return true;
}

int Player::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT))
		m_Info.Pos_X -= m_Speed * TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
		m_Info.Pos_X += m_Speed * TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_UP))
		m_Info.Pos_Y -= m_Speed * TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_DOWN))
		m_Info.Pos_Y += m_Speed * TimeDelta;

	return 0;
}

void Player::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	Rectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);

	/*HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));*/
}

void Player::Release()
{
}
