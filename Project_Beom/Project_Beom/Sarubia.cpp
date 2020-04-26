#include "pch.h"
#include "Sarubia.h"
#include "SarubiaIdleState.h"
#include "SarubiaDieState.h"

Sarubia::Sarubia()
{
}

Sarubia::~Sarubia()
{
}

bool Sarubia::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 450, 450 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 200, 250 };
	m_ObjType = OBJ_BLOCK;
	m_RenderType = RENDER_OBJ;
	m_Speed = 125.f;
	
	m_State = new SarubiaIdleState;
	m_State->Enter(this);

	m_Hp = 200;
	return true;
}

int Sarubia::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	AI();

	if (m_fallCheck)
	{
		m_GravityTime += TimeDelta;
		m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
		m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Sarubia::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 248, 248));
}

void Sarubia::Release()
{
	SAFE_DELETE(m_State);
}

void Sarubia::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
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

void Sarubia::CollisionActivate(GameObject* collideTarget)
{
	if (!m_isCollide && OBJ_PLAYER_BULLET == collideTarget->GetObjectType())
	{
		if (0 >= m_Hp)
		{
			SAFE_DELETE(m_State);
			m_State = new SarubiaDieState();
			m_State->Enter(this);
			m_isCollide = true;
			m_isCollideOn = false;
		}
	}
}

void Sarubia::AI()
{
	State* state = m_State->HandleInput(this, nullptr);
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}
