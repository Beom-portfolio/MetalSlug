#include "pch.h"
#include "Item.h"
#include "Player.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::SetItem(ITEMTYPE type)
{
	switch (type)
	{
	case ITEM_MACHINEGUN:
		SetSize(200, 200);
		m_mazentaColor = RGB(254, 254, 254);
		m_SpriteInfo.key = L"item_weapon";
		m_SpriteInfo.Speed = 0.f;
		m_CollideInfo = { 0, 0, 35, 35 };
		break;
	case ITEM_BOMB:
		SetSize(64, 60);
		m_mazentaColor = RGB(255, 0, 255);
		m_SpriteInfo.key = L"item_bomb";
		m_SpriteInfo.Speed = 10.f;
		m_SpriteInfo.MaxFrame = 6;
		m_CollideInfo = { 0, 0, 50, 50 };
		break;
	}
	m_type = type;
}

bool Item::Initialize()
{
	return true;
}

int Item::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

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

void Item::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, m_mazentaColor);
}

void Item::Release()
{
}

void Item::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
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

void Item::CollisionActivate(GameObject* collideTarget)
{
	if (m_fallCheck)
		return;

	if (!m_isCollide && OBJ_PLAYER == collideTarget->GetObjectType())
	{
		switch (m_type)
		{
		case ITEM_MACHINEGUN:
			GETMGR(SoundManager)->PlaySound(L"GetHeavy.mp3", CH_VOICE);
			((Player*)collideTarget)->AddBullet(200);
			break;
		case ITEM_BOMB:
			GETMGR(SoundManager)->PlaySound(L"Get_Item.mp3", CH_VOICE);
			GETMGR(SoundManager)->PlaySound(L"Granade.mp3", CH_VOICE);
			((Player*)collideTarget)->AddBomb(10);
			break;
		}

		m_isDead = true;
	}
}
