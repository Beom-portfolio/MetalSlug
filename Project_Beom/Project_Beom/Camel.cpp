#include "pch.h"
#include "Camel.h"
#include "CamelRestState.h"

Camel::Camel()
{
}

Camel::~Camel()
{
}

bool Camel::Initialize()
{
	m_Info = GAMEOBJINFO{ 400, 300, 200, 250 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 150, 80 };

	m_Speed = 250.f;
	m_RenderType = RENDER_OBJ;

	m_Direction = DIR_RIGHT;

	m_State = new CamelRestState;
	m_State->Enter(this);

	return true;
}

int Camel::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	HandleInput();

	// 중력
	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
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

void Camel::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
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

void Camel::CollisionActivate(GameObject* collideTarget)
{
}

void Camel::CollisionDeactivate(GameObject* collideTarget)
{
}

int Camel::UpdateInput(const float& TimeDelta)
{
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
