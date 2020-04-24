#include "pch.h"
#include "Prisoner.h"
#include "State.h"
#include "PrisonerBindState.h"
#include "PrisonerUndoState.h"
#include "PrisonerItemState.h"

Prisoner::Prisoner()
{
}

Prisoner::~Prisoner()
{
}

bool Prisoner::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 108, 145 };
	m_CollideInfo = GAMEOBJINFO{ 0, 40, 50, 50 };

	m_State = new PrisonerBindState;
	m_State->Enter(this);
	m_Speed = 150.f;

	return true;
}

int Prisoner::Update(const float& TimeDelta)
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

void Prisoner::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void Prisoner::Release()
{
	SAFE_DELETE(m_State);
}

void Prisoner::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
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

void Prisoner::CollisionActivate(GameObject* collideTarget)
{
	if (!m_isCollide && OBJ_PLAYER_BULLET == collideTarget->GetObjectType())
	{
		SAFE_DELETE(m_State);
		m_State = new PrisonerUndoState;
		m_State->Enter(this);
		m_isCollide = true;
		SetCollideInfo(GAMEOBJINFO{ 0, 40, 50, 90 });
	}
	else if(m_isCollide)
	{
		if (!m_onceCheck && OBJ_PLAYER == collideTarget->GetObjectType())
		{
			SAFE_DELETE(m_State);
			m_State = new PrisonerItemState();
			m_State->Enter(this);
			m_onceCheck = true;
			SetSize(109, 145);
		}
	}
}

void Prisoner::AI()
{
	State* state = m_State->HandleInput(this, nullptr);
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}
