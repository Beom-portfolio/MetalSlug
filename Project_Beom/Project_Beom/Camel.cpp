#include "pch.h"
#include "Camel.h"
#include "CamelRestState.h"
#include "CamelCannon.h"

Camel::Camel()
{
}

Camel::~Camel()
{
}

bool Camel::Initialize()
{
	m_Info = GAMEOBJINFO{ 400, 300, 200, 250 };
	m_CollideInfo = GAMEOBJINFO{ -20, 0, 50, 80 };

	m_Speed = 250.f;
	m_RenderType = RENDER_OBJ;

	m_Direction = DIR_RIGHT;

	m_State = new CamelRestState;
	m_State->Enter(this);

	m_Cannon = GETMGR(ObjectManager)->GetObjFromTag(L"CamelCannon", OBJ_AFTERPLAYER);
	return true;
}

int Camel::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	HandleInput();
	UpdateInput(TimeDelta);

	// 중력
	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
	}

	if (!m_rideCheck)
	{
		m_GravitySpeed = 1000.f;
		m_CollideInfo = GAMEOBJINFO{ -20, 0, 50, 80 };
		m_Cannon->SetPosition(m_Info.Pos_X - 60.f, m_Info.Pos_Y);
		((CamelCannon*)m_Cannon)->SetSpriteY(0.f);
	}
	else
	{
		m_CollideInfo = GAMEOBJINFO{ -20, 20, 50, 80 };
		m_Cannon->SetPosition(m_Info.Pos_X - 60.f, m_Info.Pos_Y - 20.f);
		((CamelCannon*)m_Cannon)->UpdateInput(TimeDelta);
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Camel::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 255, 255));

	// for test
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void Camel::Release()
{
	SAFE_DELETE(m_State);
}

void Camel::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor || PIXEL24{ 248, 0, 248 } == collPixelColor)
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
				if (!(pixelCollide->vecPixel[addr].r == collPixelColor.r &&
					pixelCollide->vecPixel[addr].g == collPixelColor.g &&
					pixelCollide->vecPixel[addr].b == collPixelColor.b))
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

			int x = (int)m_Info.Pos_X;
			int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

			const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
			if (nullptr == pixelCollide)
				return;

			// 빨간 충돌 픽셀이 아니면 내리는 작업을 하지 않는다.
			for (int i = 0; i < 10; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 248)
				{
					return;
				}
			}

			// 빨간 충돌 픽셀이 안보이면 중력 적용
			bool isRed = false;
			for (int i = 0; i < 10; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 0)
				{
					isRed = true;
				}
			}

			if (!isRed)
			{
				SetFall(true);
				return;
			}

			// 빨간 충돌 픽셀이면 아래로 내림
			int count = 0;
			for (int i = 0; i < 1000; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 0)
				{
					break;
				}
				++count;
			}
			m_Info.Pos_Y += count;
		}
	}
}

void Camel::CollisionActivate(GameObject* collideTarget)
{
}

void Camel::CollisionDeactivate(GameObject* collideTarget)
{
}

int Camel::UpdateInput(const float& TimeDelta)
{
	if (!m_fallCheck)
		m_onGroundPosY = m_Info.Pos_Y;

	if (!m_rideCheck)
	{
		if(0 != m_onGroundPosY)
			m_Info.Pos_Y = m_onGroundPosY;
		return 0;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT))
		m_Info.Pos_X -= m_Speed * TimeDelta;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
		m_Info.Pos_X += m_Speed * TimeDelta;

	if (!m_fallCheck && GETMGR(KeyManager)->GetKeyState(STATE_DOWN, 'S'))
	{
		SetFall(true);
		m_GravitySpeed = -300;
	}



	return 0;
}

void Camel::HandleInput()
{
	State* state = m_State->HandleInput(this, GETMGR(KeyManager));
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}
