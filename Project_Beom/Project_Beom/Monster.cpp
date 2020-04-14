#include "pch.h"
#include "Monster.h"

Monster::Monster()
	: GameObject()
{
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	m_Info = GAMEOBJINFO{ 200, 300, 60, 100 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 60, 100 };
	m_Speed = 500.f;
	m_ObjType = OBJ_MONSTER;
	m_RenderType = RENDER_OBJ;

	return true;
}

int Monster::Update(const float& TimeDelta)
{
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

void Monster::Render(HDC hdc)
{
	//if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
	Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void Monster::Release()
{
}

void Monster::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
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
