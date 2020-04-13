#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "PlayerBottom.h"
#include "PlayerTop.h"


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

	m_Bottom = new PlayerBottom;
	m_Bottom->Initialize();
	m_Top = new PlayerTop;
	m_Top->Initialize();

	return true;
}

int Player::Update(const float& TimeDelta)
{
	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT))
	{
		m_Info.Pos_X -= m_Speed * TimeDelta;

		if(!m_fallCheck)
			m_Direction = DIR_LEFT;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
	{
		m_Info.Pos_X += m_Speed * TimeDelta;

		if (!m_fallCheck)
			m_Direction = DIR_RIGHT;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, 'S'))
	{
		SetFall(true);
		m_GravitySpeed = -300.f;
	}

	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F2))
	{
		PLAYERWEAPON w = ((PlayerTop*)m_Top)->GetPlayerWeapon();
		(PLAYER_PISTOL == w) ? w = PLAYER_HEAVY : w = PLAYER_PISTOL;
		((PlayerTop*)m_Top)->SetPlayerWeapon(w);
		((PlayerBottom*)m_Bottom)->SetPlayerWeapon(w);
	}

	// update part
	{
		m_Bottom->SetDirection(m_Direction);
		m_Top->SetDirection(m_Direction);
		m_Bottom->SetFall(m_fallCheck);
		m_Top->SetFall(m_fallCheck);
		m_Bottom->Update(TimeDelta);
		m_Top->Update(TimeDelta);
		m_Bottom->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
		m_Top->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Player::Render(HDC hdc)
{
	/*if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	Rectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);*/

	m_Bottom->Render(hdc);
	m_Top->Render(hdc);
}

void Player::Release()
{
	SAFE_RELEASE(m_Bottom);
	SAFE_RELEASE(m_Top);
}

void Player::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
{
	if ((dir & DIR_BOTTOM))
	{
		if (m_GravitySpeed < 0)
			return;

		SetFall(false);

		// 위로 올림
		int x = (int)m_Info.Pos_X;
		int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

		const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
		if (nullptr == pixelCollide)
			return;

		int count = 0;
		for (int i = 1; i < 1000; ++i)
		{
			int addr = (int)(y - i) * pixelCollide->Width + (int)x;
			if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
			if (!(pixelCollide->vecPixel[addr].r == pixelCollide->CollPixel.r &&
				 pixelCollide->vecPixel[addr].g == pixelCollide->CollPixel.g &&
				 pixelCollide->vecPixel[addr].b == pixelCollide->CollPixel.b))
			{
				break;
			}
			++count;
		}
		m_Info.Pos_Y -= count;
	}
	else
	{
		if (m_fallCheck || m_GravitySpeed < 0)
			return;

		// 아래로 내림
		int x = (int)m_Info.Pos_X;
		int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

		const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
		if (nullptr == pixelCollide)
			return;

		int count = 0;
		for (int i = 0; i < 1000; ++i)
		{
			int addr = (int)(y + i) * pixelCollide->Width + (int)x;
			if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
			if (pixelCollide->vecPixel[addr].r == pixelCollide->CollPixel.r &&
				pixelCollide->vecPixel[addr].g == pixelCollide->CollPixel.g &&
				pixelCollide->vecPixel[addr].b == pixelCollide->CollPixel.b)
			{
				break;
			}
			++count;
		}
		m_Info.Pos_Y += count;
	}
}