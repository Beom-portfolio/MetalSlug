#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "CameraManager.h"

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

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_SPACE))
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
